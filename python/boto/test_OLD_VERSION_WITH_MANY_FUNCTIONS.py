import boto.ec2
import boto.ec2.elb
import boto.exception
import time
#import boto.ec2.blockdevicemapping.BlockDeviceType as BlockDeviceType
from fabric.api import sudo, env

###############
# EC2 instances
###############
#region = 'eu-central-1'
region = 'eu-west-1'
#ami = 'ami-23483654' # Mturk
ami = 'ami-c30b7ab4' # Docker
key_name = 'luca_2'
instance_type = 't2.micro'
security_groups = ['default-ec2-mongodb'] # select a group where port 27017 is opened!
monitoring_enabled = False
user_data = """#!/bin/bash
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

###############
# DRY RUN
###############
dry_run = False
#dry_run = True
dry_run_ok_msg = 'Request would have succeeded, but DryRun flag is set.'


def create_ebs_volumes(conn, region, dry_run=True):
    """
    Create volumes for a mongodb instance: data, journal, log.
    """
    # create EBS volumes
    volume = {}
    try:
        # data
        # TODO increase data size
        volume['/dev/xvdf'] = conn.create_volume(6, region,
            snapshot=None,
            volume_type=volume_type,
            iops=iops,
            #encrypted=False,
            dry_run=dry_run)
        # journal
        #volume['/dev/xvdg'] = conn.create_volume(5, region,
        #    snapshot=None,
        #    volume_type='io1',
        #    iops=250,
        #    #encrypted=False,
        #    dry_run=dry_run)
        # log
        volume['/dev/xvdh'] = conn.create_volume(6, region,
            snapshot=None,
            volume_type=volume_type,
            iops=iops,
            #encrypted=False,
            dry_run=dry_run)
    except boto.exception.EC2ResponseError as exc:
        if dry_run and dry_run_ok_msg in str(exc):
            pass
        else:
            raise
    return volume


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


def wait_for_volumes(volumes, state='available'):
    """ Wait for volumes to become available """
    volumes_ready = False
    while not volumes_ready:
        volumes_ready = True
        for volume in volumes:
            volume.update()
            # TODO in case of error you might wait for ever here
            if volume.status != state:
                volumes_ready = False
                time.sleep(10)
    print 'Volumes state=%s' % state


def set_fabric_env(hosts, user, instance_ids):
    """ Set some fabric env variables """
    env.hosts = hosts
    env.user = user
    env['instance_ids'] = instance_ids
    return env


def test_ssh_ready(host):
    """ Check that the SSH server is up on the provided host. In case of timeout wait and retry a
    few times. """
    import paramiko
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
        except socket.error as exc:
            if str(exc) == "timed out":
                print "SSH: %s is not ssh ready yet, connection %s" % (host, exc)
                time.sleep(10)
            #elif str(exc) == "Connection refused":
            else:
                print "SSH: %s is not ssh ready yet, %s" % (host, exc)
                time.sleep(10)
            #else:
            #    raise
    return False


def mount_ebs_volumes():
    """ Use fabric to mount the file systems on the EC2 instances """
    print env.hosts
    print env.user
    res = sudo("lsblk")
    if 'xvdf' not in res:
        raise Exception("Device /dev/xvdf not found on ec2 instance")
    res = sudo("file -s /dev/xvdf")
    if 'filesystem' not in res:
        sudo("mkfs -t ext4 /dev/xvdf")
    sudo("mkdir /data")
    sudo("mount /dev/xvdf /data")




def setup_ec2_instances():
    """ Setup the EC2 instances and corresponding EBS volumes
    """
    import base64
    conn = boto.ec2.connect_to_region(region)
    #conn.get_all_volumes()

    # run ec2 instances
    try:
        reservation = conn.run_instances(
            ami,
            min_count=1,
            max_count=1,
            key_name=key_name,
            instance_type=instance_type,
            security_groups=security_groups,
            monitoring_enabled=monitoring_enabled,
            # https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/EBSOptimized.html
            #ebs_optimized=True,
            #block_device_map={},
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
            volumes = create_ebs_volumes(conn, instance.placement, dry_run)
            wait_for_volumes(volumes.values())
            #volumes = {'/dev/xvdf': conn.get_all_volumes(volume_ids=['vol-39b8262a'])[0]}
            for volume_dev, volume in volumes.iteritems():
                print "EBS: attach volume_id=%s to instance_id=%s under %s" % (volume.id, instance.id, volume_dev)
                volume.attach(instance.id, volume_dev)
        wait_for_volumes(volumes.values(), state='in-use')
        env = set_fabric_env([instance.public_dns_name for instance in reservation.instances],
                             'ubuntu',
                             [instance.id for instance in reservation.instances])

# A collection of BlockDeviceType

def setup_ec2_instances2(conn, volume_devs):
    """ Setup the EC2 instances and corresponding EBS volumes
    """
    import base64
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
            size=6,
            volume_type='standard',
            #iops=1000,
            #encrypted=None
            )

    # run ec2 instances
    try:
        reservation = conn.run_instances(
            ami,
            min_count=1,
            max_count=1,
            key_name=key_name,
            instance_type=instance_type,
            security_groups=security_groups,
            #user_data=base64.b64encode(user_data),
            user_data=user_data,
            monitoring_enabled=monitoring_enabled,
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
        env = set_fabric_env([instance.public_dns_name for instance in reservation.instances],
                             'ubuntu',
                             [instance.id for instance in reservation.instances])

def setup_elb():
    """ Setup the ELB and register the previously created EC2 instances """
    if dry_run:
        return

    # Create load balancer
    elb_conn = boto.ec2.elb.connect_to_region(region_name=region)
    # Returns: A ResultSet containing instances of boto.ec2.elb.loadbalancer.LoadBalancer
    #elb_res_set = elb_conn.get_all_load_balancers(load_balancer_names=None)
    elb_res_set = elb_conn.get_all_load_balancers()
    for elb in elb_res_set:
        print "ELB: name=%s, dns=%s, instances=%s" % (elb.name, elb.dns_name, elb.instances)

    elb = elb_conn.create_load_balancer("Mongodb-Internal-ELB", None, #['eu-west-1c'],
                                        listeners=[(27017, 27017, 'TCP')],
                                        subnets=['subnet-96aefbfd'],
                                        security_groups=['sg-2944784c'], # mongodb security group
                                        scheme='internal', #scheme='internet-facing',
                                        complex_listeners=None)
    elb.register_instances(env['instance_ids'])
    print "ELB: name=%s, dns=%s, instances=%s" % (elb.name, elb.dns_name, elb.instances)


if __name__ == '__main__':
    conn = boto.ec2.connect_to_region(region)
    ##volumes = create_ebs_volumes(conn, region_ebs, dry_run)
    ##wait_for_volumes(volumes.values())

    setup_ec2_instances2(conn=conn, volume_devs=['/dev/xvdf'])
    ##mount_ebs_volumes()
    #setup_elb()
