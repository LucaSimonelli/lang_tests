#!/bin/bash
DEVICE='xvdf'
res=$(lsblk)
if [ $? -ne 0 ]; then
    >&2 echo "Error: \"lsblk\" return value was $?"
    exit 1
fi
if [[ ! $res =~ $DEVICE ]]; then
    >&2 echo "Error: block device /dev/$DEVICE not found"
    exit 1
fi
exit 0
res=$(sudo file -s /dev/$DEVICE)
if [ $? -ne 0 ]; then
    >&2 echo "Error: \"sudo file -s /dev/$DEVICE\" return value was $?"
    exit 1
fi
if [[ ! $res =~ 'filesystem' ]]; then
    res=$(sudo mkfs -t ext4 /dev/$DEVICE)
    if [ $? -ne 0 ]; then
        >&2 echo "Error: \"sudo mkfs -t ext4 /dev/$DEVICE\" return value was $?"
        exit 1
    fi
fi

sudo mkdir /data
if [ $? -ne 0 ]; then
    >&2 echo "Error: \"sudo mkdir /data\" return value was $?"
    exit 1
fi

sudo mount /dev/$DEVICE /data
if [ $? -ne 0 ]; then
    >&2 echo "Error: \"sudo mount /dev/$DEVICE\" return value was $?"
    exit 1
fi
exit 0
