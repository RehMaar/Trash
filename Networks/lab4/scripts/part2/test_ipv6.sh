#!/bin/sh

test_node() {
	echo ">>>>>>>> Testing $1 <<<<<<<"
	ssh "$1" '/bin/sh '
}

test_node "leibniz" <<EOF
	ping -c 3 -I ::ffff:5:7:7:1 ::ffff:5:7:8:2
	ping -c 3 -I ::ffff:5:7:7:1 ::ffff:5:7:9:3
	ping -c 3 -I ::ffff:5:7:7:1 ::ffff:5:7:0:4
EOF
test_node "ferma" <<EOF
	ping -c 3 -I ::ffff:5:7:8:2 ::ffff:5:7:7:1
	ping -c 3 -I ::ffff:5:7:8:2 ::ffff:5:7:9:3
	ping -c 3 -I ::ffff:5:7:8:2 ::ffff:5:7:0:4
EOF

test_node "kreia" <<EOF
	ping -c 3 -I ::ffff:5:7:0:4 ::ffff:5:7:8:2
	ping -c 3 -I ::ffff:5:7:0:4 ::ffff:5:7:9:3
	ping -c 3 -I ::ffff:5:7:0:4 ::ffff:5:7:7:1
EOF
test_node "rufus" <<EOF
	ping -c 3 -I ::ffff:5:7:9:3 ::ffff:5:7:7:1
	ping -c 3 -I ::ffff:5:7:9:3 ::ffff:5:7:0:4
	ping -c 3 -I ::ffff:5:7:9:3 ::ffff:5:7:8:2
EOF
