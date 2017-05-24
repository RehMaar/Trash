#!/bin/sh

configure_node() {
  ssh "$1" '/bin/sh'
}

# Gateway 3:
# 		enp0s3 -- enp0s3(Node 1)
#		enp0s9 -- enp0s3(Node 2)
#		enp0s10 -- enp0s3(Node 4) 
configure_node "rufus" <<EOF
	ip link set enp0s3 up
	ip link set enp0s9 up
	ip link set enp0s10 up

	ip a flush enp0s3
	ip a flush enp0s9
	ip a flush enp0s10

	ip a add 5.7.1.3/24 dev enp0s3
	ip a add 5.7.2.3/24 dev enp0s9
	ip a add 5.7.4.3/24 dev enp0s10

	echo 1 > /proc/sys/net/ipv4/ip_forward
EOF

# Node 4

configure_node "kreia" <<EOF
	ip link set enp0s3 up
	ip a flush enp0s3
	ip a add 5.7.4.4/24 dev enp0s3
	ip r add default via 5.7.4.3
EOF

# Node 2

configure_node "ferma" <<EOF
	ip link set enp0s3 up
	ip a flush enp0s3
	ip a add 5.7.2.2/24 dev enp0s3
	ip r add default via 5.7.2.3
EOF

# Node 1
configure_node "leibniz" <<EOF
	ip link set enp0s3 up
	ip a flush enp0s3
	ip a add 5.7.1.1/24 dev enp0s3
	ip r add default via 5.7.1.3
EOF

# ping 
configure_node "kreia" <<EOF
	ping 5.7.4.3 -c 1
	ping 5.7.2.2 -c 1
	ping 5.7.1.1 -c 1
EOF

configure_node "ferma" <<EOF
	ping 5.7.2.3 -c 1
	ping 5.7.4.4 -c 1
	ping 5.7.1.1 -c 1
EOF
configure_node "leibniz" <<EOF
	ping 5.7.1.3 -c 1
	ping 5.7.2.2 -c 1
	ping 5.7.4.4 -c 1
EOF

configure_node "rufus" <<EOF
	ping 5.7.1.1 -c 1
	ping 5.7.2.2 -c 1
	ping 5.7.4.4 -c 1
EOF

# iptables: forbid transmission on tcp port
# 	test: nc ip port (kreia) ; nc -lp port (lebniz) -- failed
# 	test: nc -u ip port (kreia) ; nc -ulp port (lebniz) -- ok
# iptables: forbid INPUT with dest A
#	ping (ip A) from someone 	-- failed
#   nc-server on rufus, nc-client on kreia -- ok
# iptables: forbid tx/rx of ICMP (length > 1000 byte & ttl < 10)
# 	test: ping -s 2000 -t 9 (ip to/from kreia) -- unreachable
# 	test: ping ip	-- good
configure_node "kreia" <<EOF
	iptables -F
	iptables -A OUTPUT -o enp0s3 -p tcp --dport 1337 -j REJECT
#    iptables -A INPUT -i enp0s3 -d 5.7.4.4 -j REJECT --reject-with icmp-host-unreachable
	iptables -A INPUT -i enp0s3 -p icmp -m length ! --length 0:1000 -m ttl --ttl-lt 10 -j REJECT
	iptables -A OUTPUT -o enp0s3 -p icmp -m length ! --length 0:1000 -m ttl --ttl-lt 10 -j REJECT
EOF

# iptables: forbid reception from udp port
# 	test: nc -ulp 1337 on (node 1); nc (node 1) 1337 -- failed
# 	test: nc -ulp 1338 on (node 1); nc (node 1) 1338 -- ok
# iptables: forbid OUTPUT with source B
# 	ping someone
configure_node "ferma" <<EOF
	iptables -F
#	iptables -A OUTPUT -o enp0s3 -s 5.7.2.2 -j REJECT --reject-with icmp-host-unreachable
	iptables -A INPUT -i enp0s3 -p udp --sport 1337 -j REJECT
EOF
