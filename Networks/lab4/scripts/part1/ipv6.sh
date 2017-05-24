
#!/bin/sh

configure_node() {
  ssh "$1" '/bin/sh'
}

# Node 3 (enp0s3)  -> Node 1 (enp0s3) [int1]
# Node 3 (enp0s9)  -> Node 2 (enp0s3) [int2]
# Node 3 (enp0s10) -> Node 4 (enp0s3) [int3]

# Node 3
echo "Configure Rufus"
configure_node "rufus" <<EOF
  ip link set enp0s3 up
  ip link set enp0s9 up
  ip link set enp0s10 up
  ip -6 addr add ::ffff:5:7:1:1/126 dev enp0s3
  ip -6 addr add ::ffff:5:7:2:1/126 dev enp0s9
  ip -6 addr add ::ffff:5:7:3:1/126 dev enp0s10
  echo 1 | tee /proc/sys/net/ipv6/conf/*/forwarding > /dev/null
  echo 0 | tee /proc/sys/net/ipv6/conf/*/accept* > /dev/null
#  echo 0 | tee /proc/sys/net/ipv6/conf/*/autoconf > /dev/null
  ip6tables -t nat -F
  ip6tables -t nat -A PREROUTING -d ::ffff:5:7:9:9/128 -i enp0s10 -p udp -j DNAT --to-destination ::ffff:5:7:1:2
  ip6tables -t nat -A POSTROUTING -d ::ffff:5:7:3:2/128 -p udp -j SNAT --to-source ::ffff:5:7:9:9
  ip6tables -t mangle -F
  ip6tables -t mangle -A PREROUTING -d ::ffff:5:7:9:9/128 -i enp0s10 -p udp -j TEE --gateway ::ffff:5:7:2:2
  ip6tables -t raw -F
  ip6tables -t raw -A PREROUTING -s ::ffff:5:7:9:9 -p udp -j NOTRACK
EOF

# Node 1
echo "Configure Leibniz"
configure_node "leibniz" <<EOF
  ip link set enp0s3 up
  ip -6 addr add ::ffff:5:7:1:2/126 dev enp0s3
  ip -6 route add default via ::ffff:5:7:1:1
#  echo 0 | tee /proc/sys/net/ipv6/conf/*/accept* > /dev/null
#  echo 0 | tee /proc/sys/net/ipv6/conf/*/autoconf > /dev/null
EOF

# Node 2
echo "Configure Ferma"
configure_node "ferma" <<EOF
  ip link set enp0s3 up
  ip -6 addr add ::ffff:5:7:2:2/126 dev enp0s3
  ip -6 route add default via ::ffff:5:7:2:1
  ip6tables -t nat -F
  ip6tables -t nat -A PREROUTING -d ::ffff:5:7:9:9/128 -i enp0s3 -p udp -j DNAT --to-destination ::ffff:5:7:2:2
EOF

# Node 4
echo "Configure Kreia"
configure_node "kreia" <<EOF
  ip link set enp0s3 up
  ip -6 addr add ::ffff:5:7:3:2/126 dev enp0s3
  ip -6 route add default via ::ffff:5:7:3:1
EOF

## Check ping
#echo "Check Rufus"
#configure_node "rufus" <<EOF
#	ping -c 1 ::ffff:5:7:3:2 >/dev/null 2>&1 && echo "Kreia is alive" || echo "Kreia is dead" 
#	ping -c 1 ::ffff:5:7:1:2 >/dev/null 2>&1 && echo "Leibniz is alive || echo "Leibniz is dead"
#	ping -c 1 ::ffff:5:7:2:2 >/dev/null 2>&1 && echo "Ferma is alive || echo "Ferma is dead"
#EOF
#
#echo "Check Kreia"
#configure_node "kreia" <<EOF
#	ping -c 1 ::ffff:5:7:3:1 >/dev/null 2>&1  && echo "Keria's gate is alive"  || echo "Kreia's gate is dead"
#	ping -c 1 ::ffff:5:7:2:1 >/dev/null 2>&1  && echo "Ferma's gate is alive"  || echo "Ferma's is dead"
#	ping -c 1 ::ffff:5:7:1:1 >/dev/null 2>&1  && echo "Leibniz' gate is alive" || echo "Leibniz' gate is dead"
#	ping -c 1 ::ffff:5:7:2:2 >/dev/null 2>&1  && echo "Ferma is alive"         || echo "Ferma is dead"
#	ping -c 1 ::ffff:5:7:1:2 >/dev/null 2>&1  && echo "Leibniz is alive"       || echo "Leibniz is dead"
#EOF
#
#echo "Check Ferma"
#configure_node "ferma" <<EOF
#	ping -c 1 ::ffff:5:7:2:1 >/dev/null 2>&1  && echo "Ferma's gate is alive"  || echo "Ferma's is dead"
#	ping -c 1 ::ffff:5:7:1:1 >/dev/null 2>&1  && echo "Leibniz' gate is alive" || echo "Leibniz' gate is dead"
#	ping -c 1 ::ffff:5:7:3:1 >/dev/null 2>&1  && echo "Keria's gate is alive"  || echo "Kreia's gate is dead"
#	ping -c 1 ::ffff:5:7:3:2 >/dev/null 2>&1  && echo "Kreia is alive"         || echo "Kreia is dead"
#	ping -c 1 ::ffff:5:7:1:2 >/dev/null 2>&1  && echo "Leibniz is alive"       || echo "Leibniz is dead"
#EOF
#
#
#echo "Check Leibniz"
#configure_node "leibniz" <<EOF
#	ping -c 1 ::ffff:5:7:1:1 >/dev/null 2>&1  && echo "Leibniz' gate is alive" || echo "Leibniz' gate is dead"
#	ping -c 1 ::ffff:5:7:3:1 >/dev/null 2>&1  && echo "Keria's gate is alive"  || echo "Kreia's gate is dead"
#	ping -c 1 ::ffff:5:7:2:1 >/dev/null 2>&1  && echo "Ferma's gate is alive"  || echo "Ferma's is dead"
#	ping -c 1 ::ffff:5:7:3:2 >/dev/null 2>&1  && echo "Kreia is alive"         || echo "Kreia is dead"
#	ping -c 1 ::ffff:5:7:2:2 >/dev/null 2>&1  && echo "Ferma is alive"         || echo "Ferma is dead"
#EOF
