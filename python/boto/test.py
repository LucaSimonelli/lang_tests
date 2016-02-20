import boto.ec2
import boto.ec2.elb
import boto.exception
import time

###############
# EC2 instances
###############
#ec2_region = 'eu-central-1'
ec2_region = 'eu-west-1'
#ec2_ami = 'ami-23483654' # Mturk
ec2_ami = 'ami-c30b7ab4' # Docker
ec2_key_name = 'luca_2'
ec2_instance_type = 't2.micro'
ec2_security_groups = ['default-ec2-mongodb'] # select a group where port 27017 is opened!
ec2_monitoring_enabled = False
ec2_user_data = """#!/bin/bash
LOG=/var/log/mounting_ebs.log
echo "Start mounting EBS volumes" >> $LOG

DEVICE='xvdf'
MOUNT_POINT='/data'
res=$(lsblk)
ret=$?
if [ $ret -ne 0 ]; then
    >&2 echo "Error: \"lsblk\" return value was $ret" >> $LOG
    exit 1
fi
if [[ ! $res =~ $DEVICE ]]; then
    >&2 echo "Error: block device /dev/$DEVICE not found" >> $LOG
    exit 1
fi

res=$(sudo file -s /dev/$DEVICE)
ret=$?
if [ $ret -ne 0 ]; then
    >&2 echo "Error: \"sudo file -s /dev/$DEVICE\" return value was $ret" >> $LOG
    exit 1
fi
if [[ ! $res =~ 'filesystem' ]]; then
    res=$(sudo mkfs -t ext4 /dev/$DEVICE)
    ret=$?
    if [ $ret -ne 0 ]; then
        >&2 echo "Error: \"sudo mkfs -t ext4 /dev/$DEVICE\" return value was $ret" >> $LOG
        exit 1
    fi  
fi

if [ ! -d $MOUNT_POINT ]; then
    sudo mkdir /data
    ret=$?
    if [ $ret -ne 0 ]; then
        >&2 echo "Error: \"sudo mkdir /data\" return value was $ret" >> $LOG
        exit 1
    fi
fi

sudo mount /dev/$DEVICE $MOUNT_POINT -t ext4
ret=$?
if [ $ret -ne 0 ]; then
    >&2 echo "Error: \"sudo mount /dev/$DEVICE\" return value was $ret" >> $LOG
    exit 1
fi
echo "EBS volumes mounted OK" >> $LOG
exit 0
"""

###############
# EBS Volumes
###############
ebs_volume_type = 'standard'
#ebs_volume_type = 'io1'
ebs_iops = None
#ebs_iops = 1000
ebs_region = 'eu-west-1c'
ebs_size = 6 # Gb

###############
# ELB params
###############
elb_name = "Mongodb-Internal-ELB"
elb_region = None
elb_listeners = [(27017, 27017, 'TCP')]
elb_subnets = ['subnet-96aefbfd']
elb_security_groups = ['sg-2944784c'] # mongodb security group
elb_scheme = 'internal' # or 'internet-facing'

###############
# DRY RUN
###############
dry_run = False
#dry_run = True
dry_run_ok_msg = 'Request would have succeeded, but DryRun flag is set.'


def wait_for_instances(instances):
    """ Wait for instances to become ready """
    instances_ready = False
    while not instances_ready:
        instances_ready = True
        for instance in instances:
            status = instance.update()
            if status == 'pending':
                instances_ready = False
                time.sleep(10)
            elif instance.public_dns_name is None or \
                 not test_ssh_ready(instance.public_dns_name):
                instances_ready = False
                time.sleep(10)
    print 'Instances ready'


def test_ssh_ready(host):
    """ Check that the SSH server is up on the provided host. In case of timeout wait and retry a
    few times. """
    import paramiko
    import errno
    import socket
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    retries = 10
    while retries > 0:
        retries -= 1
        try:
            # no key provided as this makes use of the local .ssh/config
            ssh.connect(host, username='ubuntu', timeout=10) #, key_filename=key_file)
            return True
        except socket.timeout as exc:
            print "SSH: %s is not ssh ready yet, connection %s" % (host, exc)
            time.sleep(10)
        except socket.error as exc:
            if exc.errno == errno.ECONNREFUSED:
                print "SSH: %s is not ssh ready yet, %s" % (host, exc)
                time.sleep(10)
            else:
                raise
    return False


def setup_ec2_instances(conn, volume_devs):
    """ Setup the EC2 instances and corresponding EBS volumes
    """
    #import base64
    import boto.ec2.blockdevicemapping
    #conn.get_all_volumes()
    block_device_map = boto.ec2.blockdevicemapping.BlockDeviceMapping()
    for volume_dev in volume_devs:
        block_device_map[volume_dev] = boto.ec2.blockdevicemapping.BlockDeviceType(
            connection=conn,
            #ephemeral_name='xvdf',
            #no_device=False,
            #volume_id=volume.id,
            #snapshot_id=None,
            #status=None,
            #attach_time=None,
            delete_on_termination=False,
            size=ebs_size,
            volume_type=ebs_volume_type,
            #iops=1000,
            #encrypted=None
            )

    # run ec2 instances
    try:
        reservation = conn.run_instances(
            ec2_ami,
            min_count=1,
            max_count=1,
            key_name=ec2_key_name,
            instance_type=ec2_instance_type,
            security_groups=ec2_security_groups,
            #user_data=base64.b64encode(ec2_user_data),
            user_data=ec2_user_data,
            monitoring_enabled=ec2_monitoring_enabled,
            # https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/EBSOptimized.html
            #ebs_optimized=True,
            block_device_map=block_device_map,
            dry_run=dry_run)
    except boto.exception.EC2ResponseError as exc:
        if dry_run and dry_run_ok_msg in str(exc):
            pass
        else:
            raise

    # Create ESB volumes and attach them to the EC2 instances
    if not dry_run:
        wait_for_instances(reservation.instances)
        for instance in reservation.instances:
            print "EC2: instance_id=%s, region=%s" % (instance.id, instance.placement)
        return [instance.id for instance in reservation.instances]
    return []


def setup_elb(instance_ids):
    """ Setup the ELB and register the provided EC2 instances """
    if dry_run:
        return

    elb_conn = boto.ec2.elb.connect_to_region(region_name=ec2_region)
    elb = elb_conn.create_load_balancer(elb_name, elb_region,
                                        listeners=elb_listeners,
                                        subnets=elb_subnets,
                                        security_groups=elb_security_groups,
                                        scheme=elb_scheme)
    elb.register_instances(instance_ids)
    print "ELB: name=%s, dns=%s, instances=%s" % (elb.name, elb.dns_name, elb.instances)


if __name__ == '__main__':
    conn = boto.ec2.connect_to_region(ec2_region)
    instance_ids = setup_ec2_instances(conn=conn, volume_devs=['/dev/xvdf'])
    setup_elb(instance_ids)
