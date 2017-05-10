#!/bin/bash

function usage {
	echo "usage: check_hosts ipv4|ipv6 ID MAXID"
}

# get_ipv4 ID
function get_ipv4 {
	echo "5.7.1.$1"
}

# get_ipv6 ID
function get_ipv6 {
	printf "0:0:0:0:0:ffff:%x%x%x:%x%x%x" 5 0 7 1 0 $1
}

# check_hosts VERSION ID MAXID
function check_hosts {
	local version=$1
	local id=$2
	local maxid=$3
	local dev="enp0s3"
	local i=1
	local ip=""
	local cmd=""

	echo "Check other hosts."
	maxid=$((maxid+1))
	for i in $(seq 2 $maxid); do
		if [ ! "$i" = "$id" ] ; then
			case "$version" in
				"ipv4") 
					ip=`get_ipv4 $i`
					cmd="ping -c 1 -I $dev $ip"
					;;
				"ipv6") 
					local ip=`get_ipv6 $i`
					cmd="ping -6 -c 1 -I $dev $ip"
					;;
				*)
					echo "Wrong IP version"
					exit 1
					;;
			esac
			if $($cmd > /dev/null) ; then
				echo "Host $ip is alive."
			else
				echo "Host $ip is dead."
			fi
		fi
	done
}

[ $# = 3 ] || { usage ; exit ; }

VERSION=$1
ID=$2
MAXID=$3

check_hosts $VERSION $ID $MAXID
