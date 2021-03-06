#!/bin/sh
tmpdir="test"
mkdir  $tmpdir
count=0
while IFS= read -r userhost; do
    ssh -n -o BatchMode=yes ${userhost} '/sbin/ifconfig' > ${tmpdir}/${userhost} 2>&1 &
    count=`expr $count + 1`
done < hosts
while [ $count -gt 0 ]; do
    wait $pids
    count=`expr $count - 1`
done
echo "Output for hosts are in $tmpdir"

