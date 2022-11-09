#!/usr/bin/env bash

#Define the boot path since cppst0rm was designed to handle
#multiple device's boot files
bootpath="../boot/$1"
bootlogo="$2"

if [ "$1" == "" ]; then
    echo "This boot script is meant to be only run by cppst0rm. Please use the '-b' argument. It will check for a boot folder with your specified board config to boot your iDevice. No need to deal with two different programs/scripts!"
    exit
fi

if [ "$2" == "" ]; then
    echo "This boot script is meant to be only run by cppst0rm. Please use the '-b' argument. It will check for a boot folder with your specified board config to boot your iDevice. No need to deal with two different programs/scripts!"
    exit
fi

cpid=$(irecovery -q | grep "CPID" | sed "s/CPID: //")

echo "Sending iBSS..."
irecovery -f $bootpath/ibss.img4
sleep 2
echo "Sending iBEC..."
irecovery -f $bootpath/ibec.img4
sleep 2

if [[ "$cpid" == *"0x80"* ]]; then
    irecovery -f boot/iBEC.img4
    sleep 2
    irecovery -c "go"
fi

if [ "$bootlogo" == "YES" ]; then
    echo "Sending bootlogo..."
    irecovery -f $bootpath/bootlogo.img4
    echo "Setting picture..."
    irecovery -c "setpicture 0x1"
fi

echo "Sending devicetree..."
irecovery -f $bootpath/devicetree.img4
echo "Running 'devicetree'"
irecovery -c "devicetree"
echo "Sending trustcache..."
irecovery -f $bootpath/trustcache.img4
echo "Running 'firmware'..."
irecovery -c "firmware"
echo "Sending krnlboot..."
irecovery -f $bootpath/krnlboot.img4
echo "Booting..."
irecovery -c "bootx"
