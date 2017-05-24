#!/bin/sh

configure_node() {
  ssh "$1" '/bin/sh'
}

# Node 3 (enp0s3)  -> Node 1 (enp0s3) [int1]
# Node 3 (enp0s9)  -> Node 2 (enp0s3) [int2]
# Node 3 (enp0s10) -> Node 4 (enp0s3) [int3]

# Node 3
configure_node "rufus" <<EOF
  ip link set enp0s3 up
  ip link set enp0s9 up
  ip link set enp0s10 up
  ip addr flush dev enp0s3
  ip addr flush dev enp0s9
  ip addr flush dev enp0s10
  ip addr add 5.7.1.1/30 dev enp0s3
  ip addr add 5.7.2.1/30 dev enp0s9
  ip addr add 5.7.3.1/30 dev enp0s10
  echo 1 > /proc/sys/net/ipv4/ip_forward
  echo 0 | tee /proc/sys/net/ipv4/conf/*/rp_filter > /dev/null
  iptables -t nat -F
  iptables -t nat -A PREROUTING -i enp0s10 -d 5.7.42.42 -p udp -j DNAT --to-destination 5.7.1.2
  iptables -t nat -A POSTROUTING -d 5.7.3.2 -p udp -j SNAT --to-source 5.7.42.42
  iptables -t mangle -F
  iptables -t mangle -A PREROUTING -i enp0s10 -d 5.7.42.42 -p udp -j TEE --gateway 5.7.2.2
  iptables -t raw -F
  iptables -t raw -A PREROUTING -s 5.7.42.42 -p udp -j NOTRACK
EOF

# Node 1
configure_node "leibniz" <<EOF
  ip link set enp0s3 up
  ip addr flush dev enp0s3
  ip addr add 5.7.1.2/30 dev enp0s3
  ip route add default via 5.7.1.1
EOF

# Node 2
configure_node "ferma" <<EOF
  ip link set enp0s3 up
  ip addr flush dev enp0s3
  ip addr add 5.7.2.2/30 dev enp0s3
  ip route add default via 5.7.2.1
  iptables -t nat -F
  iptables -t nat -A PREROUTING -p udp -d 5.7.42.42 -j DNAT --to-dest 5.7.2.2
EOF

# Node 4
configure_node "kreia" <<EOF
  ip link set enp0s3 up
  ip addr flush dev enp0s3
  ip addr add 5.7.3.2/30 dev enp0s3
  ip route add default via 5.7.3.1
EOF
