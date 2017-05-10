#!/bin/bash

function usage {
	echo -e "usage: netconfig.bash ipv4|ipv6 mask id\n" \
		"	mask  -- the mask in the CIDR format\n"\
		"	id    -- the id of the host in the system"
}

# unset_ip dev
function unset_ip  {
	ip a flush $1
}

# set_ip ip mask dev
function set_ip {
	local version=$1
	local ip=$2
	local mask=$3
	local dev=$4
	local cmd="false"
	case $version in
		"ipv4") 
				ip a add $ip/$mask dev $dev || echo "netconfig: Cannot set $ip address to $dev"
			;;
		"ipv6")
				ip -6 a add $ip/$mask dev $dev || echo "netconfig: Cannot set $ip address to $dev"
			;;
	esac
}

function up_dev {
	ip link set "$1" up
}

function down_dev {
	ip link set "$1" down
}

# set_forwarding ipv4|ipv6
function set_forwarding {
	local version=$1
	local forwarding_path="/proc/sys/net"

	case "$version" in
		"ipv4") 
			forwarding_path+="/ipv4/ip_forward"  
			;;
		"ipv6") 
			forwarding_path+="/ipv6/conf/default/forwarding"
			;;
		*)
			echo "Wrong IP version."
			exit 1
	esac

	local is_set=`cat "$forwarding_path"`

	[[ $is_set = 1 ]] && exit 0
	
	echo 1 > "$forwarding_path"
}

[[ ! $# = 3 ]] && { usage ; exit ;}

# Address format: A.B.X.Y/M
# A -- 5
# B -- 7
# X -- 1
# Y -- the ID of the host in the host system
# M -- mask 

VERSION=$1
MASK=$2
ID=$3

IP=""

case $VERSION in
	"ipv4") IP="5.7.1.$ID"
		;;
	"ipv6")
		IP=`printf "0:0:0:0:0:ffff:%x%x%x:%x%x%x" 5 0 7 1 0 $ID`
		;;
esac

# Clear device
echo "netconfig: Down device enp0s3"
down_dev "enp0s3"  
echo "netconfig: Unset IP addresses on the device"
unset_ip "enp0s3"

# Set ip and up device
echo "netconfig: Set new IP address $IP"
set_ip $VERSION $IP $MASK "enp0s3"
echo "netconfig: Up device enp0s3"
up_dev "enp0s3"

#Set ip forwarding
echo "netconfig: Set forwarding"
set_forwarding  $VERSION
