#!/bin/bash

function usage {
	echo "usage: configure.bash ipv4|ipv6 hostnames.."
}

# fn verion list
function execute_netconfig {
	local version=$1
	local list=($@)
	local maxid=$#

	maxid=$((maxid-1))
	list=${list/$1}

    for i in $(seq 1 $maxid); do
		local host=${list[i]}
    	scp root@$host:~ netconfig.bash
		i=$((i+1))
    	ssh root@$host "bash netconfig.bash $version 24 $i $maxid"
    done
}

#fn version list
function execut_check_hosts {
	local version=$1
	local list=($@)
	local maxid=$#

	maxid=$((maxid-1))
	list=${list/$1}

    for i in $(seq 1 $maxid); do
		local host=${list[i]}
    	scp root@$host:~ check_hosts.bash
		i=$((i+1))
    	ssh root@$host "bash check_hosts.bash $version $i $maxid"
    done
}

execute_netconfig $@
execut_check_hosts $@
