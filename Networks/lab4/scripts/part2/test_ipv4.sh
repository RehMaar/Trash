#!/bin/sh

test_node() {
	echo "Testing $1"
	ssh "$1" '/bin/sh '
}

test_node "leibniz" <<EOF
	ping -c 3 -I 5.7.7.1 5.7.8.2
	ping -c 3 -I 5.7.7.1 5.7.9.3
	ping -c 3 -I 5.7.7.1 5.7.0.4
EOF
test_node "ferma" <<EOF
	ping -c 3 -I 5.7.8.2 5.7.7.1
	ping -c 3 -I 5.7.8.2 5.7.9.3
	ping -c 3 -I 5.7.8.2 5.7.0.4
EOF
test_node "rufus" <<EOF
	ping -c 3 -I 5.7.9.3 5.7.8.2
	ping -c 3 -I 5.7.9.3 5.7.7.1
	ping -c 3 -I 5.7.9.3 5.7.0.4
EOF
test_node "kreia" <<EOF
	ping -c 3 -I 5.7.0.4 5.7.8.2
	ping -c 3 -I 5.7.0.4 5.7.9.3
	ping -c 3 -I 5.7.0.4 5.7.7.1
EOF
