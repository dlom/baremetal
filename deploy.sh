#!/usr/bin/env zsh

if [[ $UID == 0 || $EUID == 0 ]]; then
    echo "mounting SD card..."
    mount /dev/mmcblk0p1 sd
    echo "making sure kernel.img is up to date..."
    make kernel.img
    echo "copying kernel.img over..."
    cp kernel.img sd/
    echo "unmount SD card..."
    umount sd
    echo "syncing data..."
    sync
else
    echo "run as root"
fi
