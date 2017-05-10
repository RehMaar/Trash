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
		i=$((i+1))
		echo "$host $i"
    	scp netconfig.bash $host:~
    	ssh $host "bash netconfig.bash $version 24 $i"
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
		echo $host
    	scp check_hosts.bash root@$host:~ 
		i=$((i+1))
    	ssh root@$host "bash check_hosts.bash $version $i $maxid"
    done
}

echo "configure: Configure netwrok."
execute_netconfig $@
echo "configure: Test hosts."
execut_check_hosts $@
