#!/bin/bash

function usage {
	echo "usage: set_iptable.bash host file"
}

[ "$#" = "0" ] && { usage ; exit ; }

host=$1
filepath=$2
file=`basename $filepath`

scp "$filepath" $host:~
ssh $host "iptables-restore $file"
