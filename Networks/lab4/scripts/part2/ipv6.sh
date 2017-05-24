#!/bin/sh

configure_node() {

  alias ip='ip -6'
    echo "Configure $1"
    ssh "$1" '/bin/sh'
}

# Node 1: ::ffff:5:7:7:1/128 dev lo
#   (int4) enp0s9  <-> enp0s9 Node 2
#   (int1) enp0s3  <-> enp0s3 Node 3
#   (int6) enp0s10 <-> enp0s10 Node 4
#
# Node 2: ::ffff:5:7:8:2/128 dev lo
#   (int4) enp0s9  <-> enp0s9 Node 1
#   (int2) enp0s3  <-> enp0s3 Node 3
#   (int5) enp0s10 <-> enp0s9 Node 4
#
# Node 3: ::ffff:5:7:9:3/128 dev lo
#   (int1) enp0s3  <-> enp0s3 Node 1
#   (int2) enp0s9  <-> enp0s3 Node 2 
#   (int3) enp0s10 <-> enp0s3 Node 4
#
# Node 4: ::ffff:5:7:0:4/128 dev lo
#   (int6) enp0s10 <-> enp0s10 Node 1
#   (int5) enp0s9  <-> enp0s10 Node 2
#   (int3) enp0s3  <-> enp0s10 Node 3
#


# Node 1
configure_node "leibniz" <<EOF
  alias ip='ip -6'
  ip link set enp0s3 up
  ip link set enp0s9 up
  ip link set enp0s10 up

  ip addr add ::ffff:5:7:1:1/120 dev enp0s3
  ip addr add ::ffff:5:7:4:1/120 dev enp0s9
  ip addr add ::ffff:5:7:6:1/120 dev enp0s10

  ip addr add ::ffff:5:7:7:1/128 dev lo

  echo 1 | tee /proc/sys/net/ipv6/conf/*/forwarding > /dev/null
  echo 2 | tee /proc/sys/net/ipv6/conf/*/accept_ra > /dev/null

EOF

# Node 2
configure_node "ferma" <<EOF

  alias ip='ip -6'
  ip link set enp0s3 up
  ip link set enp0s9 up
  ip link set enp0s10 up

  ip addr add ::ffff:5:7:2:2/120 dev enp0s3
  ip addr add ::ffff:5:7:4:2/120 dev enp0s9
  ip addr add ::ffff:5:7:5:2/120 dev enp0s10

  ip addr add ::ffff:5:7:8:2/128 dev lo

  echo 1 | tee /proc/sys/net/ipv6/conf/*/forwarding > /dev/null
  echo 2 | tee /proc/sys/net/ipv6/conf/*/accept_ra > /dev/null

EOF

# Node 3
configure_node "rufus" <<EOF

  alias ip='ip -6'
  ip link set enp0s3 up
  ip link set enp0s9 up
  ip link set enp0s10 up

  ip addr add ::ffff:5:7:1:3/120 dev enp0s3
  ip addr add ::ffff:5:7:2:3/120 dev enp0s9
  ip addr add ::ffff:5:7:3:3/120 dev enp0s10

  ip addr add ::ffff:5:7:9:3/128 dev lo

  echo 1 | tee /proc/sys/net/ipv6/conf/*/forwarding > /dev/null
  echo 2 | tee /proc/sys/net/ipv6/conf/*/accept_ra > /dev/null
EOF

# Node 4
configure_node "kreia" <<EOF
  alias ip='ip -6'
  ip link set enp0s3 up
  ip link set enp0s9 up
  ip link set enp0s10 up

  ip addr add ::ffff:5:7:3:4/120 dev enp0s3
  ip addr add ::ffff:5:7:5:4/120 dev enp0s9
  ip addr add ::ffff:5:7:6:4/120 dev enp0s10

  ip addr add ::ffff:5:7:0:4/128 dev lo

  echo 1 | tee /proc/sys/net/ipv6/conf/*/forwarding > /dev/null
  echo 2 | tee /proc/sys/net/ipv6/conf/*/accept_ra > /dev/null

EOF


configure_node "leibniz" <<EOF
  alias ip='ip -6'
    ip rule add prio 100 from ::ffff:5:7:7:1 table 1
    ip r add ::ffff:5:7:8:2 table 1 nexthop via ::ffff:5:7:4:2 weight 1 \
                             nexthop via ::ffff:5:7:1:3 weight 2 \
                             nexthop via ::ffff:5:7:6:4 weight 3
    ip r add ::ffff:5:7:9:3 table 1 nexthop via ::ffff:5:7:4:2 weight 1 \
                             nexthop via ::ffff:5:7:1:3 weight 2 \
                             nexthop via ::ffff:5:7:6:4 weight 3
    ip r add ::ffff:5:7:0:4 table 1 nexthop via ::ffff:5:7:4:2 weight 1 \
                             nexthop via ::ffff:5:7:1:3 weight 2 \
                             nexthop via ::ffff:5:7:6:4 weight 3

    ip rule add prio 100 from ::ffff:5:7:8:2 table 2
    ip r add ::ffff:5:7:9:3 table 2 nexthop via ::ffff:5:7:1:3 weight 2
    ip r add ::ffff:5:7:0:4 table 2 nexthop via ::ffff:5:7:4:2 weight 1

    ip rule add prio 100 from ::ffff:5:7:9:3 table 3
    ip r add ::ffff:5:7:8:2 table 3 nexthop via ::ffff:5:7:4:2 weight 1
    ip r add ::ffff:5:7:0:4 table 3 nexthop via ::ffff:5:7:6:4 weight 3

    ip rule add prio 100 from ::ffff:5:7:0:4 table 4
    ip r add ::ffff:5:7:9:3 table 4 nexthop via ::ffff:5:7:1:3 weight 2
    ip r add ::ffff:5:7:8:2 table 4 nexthop via ::ffff:5:7:4:2 weight 1
EOF
configure_node "ferma" <<EOF
  alias ip='ip -6'
    ip rule add prio 100 from ::ffff:5:7:8:2 table 2
    ip r add ::ffff:5:7:7:1 table 2 nexthop via ::ffff:5:7:4:1 weight 1 \
                             nexthop via ::ffff:5:7:2:3 weight 3 \
                             nexthop via ::ffff:5:7:5:4 weight 2
    ip r add ::ffff:5:7:9:3 table 2 nexthop via ::ffff:5:7:4:1 weight 1 \
                             nexthop via ::ffff:5:7:2:3 weight 3 \
                             nexthop via ::ffff:5:7:5:4 weight 2
    ip r add ::ffff:5:7:0:4 table 2 nexthop via ::ffff:5:7:4:1 weight 1 \
                             nexthop via ::ffff:5:7:2:3 weight 3 \
                             nexthop via ::ffff:5:7:5:4 weight 2

    ip rule add prio 100 from ::ffff:5:7:7:1 table 1
    ip r add ::ffff:5:7:9:3 table 1 nexthop via ::ffff:5:7:2:3 weight 3 
    ip r add ::ffff:5:7:0:4 table 1 nexthop via ::ffff:5:7:5:4 weight 2

    ip rule add prio 100 from ::ffff:5:7:9:3 table 3
    ip r add ::ffff:5:7:7:1 table 3 nexthop via ::ffff:5:7:4:1 weight 1
    ip r add ::ffff:5:7:0:4 table 3 nexthop via ::ffff:5:7:5:4 weight 2

    ip rule add prio 100 from ::ffff:5:7:0:4 table 4
    ip r add ::ffff:5:7:7:1 table 4 nexthop via ::ffff:5:7:4:1 weight 1
    ip r add ::ffff:5:7:9:3 table 4 nexthop via ::ffff:5:7:2:3 weight 3 
EOF

configure_node "rufus" <<EOF
  alias ip='ip -6'
    ip rule add prio 100 from ::ffff:5:7:9:3 table 3
    ip r add ::ffff:5:7:8:2 table 3 nexthop via ::ffff:5:7:2:2 weight 3 \
                             nexthop via ::ffff:5:7:1:1 weight 2 \
                             nexthop via ::ffff:5:7:3:4 weight 1
    ip r add ::ffff:5:7:7:1 table 3 nexthop via ::ffff:5:7:2:2 weight 3 \
                             nexthop via ::ffff:5:7:1:1 weight 2 \
                             nexthop via ::ffff:5:7:3:4 weight 1
    ip r add ::ffff:5:7:0:4 table 3 nexthop via ::ffff:5:7:2:2 weight 3 \
                             nexthop via ::ffff:5:7:1:1 weight 2 \
                             nexthop via ::ffff:5:7:3:4 weight 1
   
    ip rule add prio 100 from ::ffff:5:7:7:1 table 1
    ip r add ::ffff:5:7:8:2 table 1 nexthop via ::ffff:5:7:2:2 weight 3
    ip r add ::ffff:5:7:0:4 table 1 nexthop via ::ffff:5:7:3:4 weight 1

    ip rule add prio 100 from ::ffff:5:7:8:2 table 2
    ip r add ::ffff:5:7:7:1 table 2 nexthop via ::ffff:5:7:1:1 weight 2
    ip r add ::ffff:5:7:0:4 table 2 nexthop via ::ffff:5:7:3:4 weight 1

    ip rule add prio 100 from ::ffff:5:7:0:4 table 4
    ip r add ::ffff:5:7:8:2 table 4 nexthop via ::ffff:5:7:2:2 weight 3
    ip r add ::ffff:5:7:7:1 table 4 nexthop via ::ffff:5:7:1:1 weight 2
EOF
configure_node "kreia" <<EOF
  alias ip='ip -6'
    ip rule add prio 100 from ::ffff:5:7:0:4 table 4
    ip r add ::ffff:5:7:8:2 table 4 nexthop via ::ffff:5:7:5:2 weight 2 \
                             nexthop via ::ffff:5:7:3:3 weight 1 \
                             nexthop via ::ffff:5:7:6:1 weight 3
    ip r add ::ffff:5:7:9:3 table 4 nexthop via ::ffff:5:7:5:2 weight 2 \
                             nexthop via ::ffff:5:7:3:3 weight 1 \
                             nexthop via ::ffff:5:7:6:1 weight 3
    ip r add ::ffff:5:7:7:1 table 4 nexthop via ::ffff:5:7:5:2 weight 2 \
                             nexthop via ::ffff:5:7:3:3 weight 1 \
                             nexthop via ::ffff:5:7:6:1 weight 3

    ip rule add prio 100 from ::ffff:5:7:7:1 table 1
    ip r add ::ffff:5:7:8:2 table 1 nexthop via ::ffff:5:7:5:2 weight 2
    ip r add ::ffff:5:7:9:3 table 1 nexthop via ::ffff:5:7:3:3 weight 1

	ip rule add prio 100 from ::ffff:5:7:8:2 table 2
    ip r add ::ffff:5:7:9:3 table 2 nexthop via ::ffff:5:7:3:3 weight 1
    ip r add ::ffff:5:7:7:1 table 2 nexthop via ::ffff:5:7:6:1 weight 3

	ip rule add prio 100 from ::ffff:5:7:9:3 table 3
    ip r add ::ffff:5:7:8:2 table 3 nexthop via ::ffff:5:7:5:2 weight 3
    ip r add ::ffff:5:7:7:1 table 3 nexthop via ::ffff:5:7:6:1 weight 3
EOF



#configure_node "leibniz" <<EOF
#  # From Node 1
#  ip rule add prio 100 from ::ffff:5:7:7:1 table 1
#  # To Node 4
#  ip r add ::ffff:5:7:0:4 table 1 nexthop via ::ffff:5:7:6:4 weight 3 \
#                           nexthop via ::ffff:5:7:4:2 weight 1 \
#                           nexthop via ::ffff:5:7:1:3 weight 2
#  # To Node 3
#  ip r add ::ffff:5:7:9:3 table 1 nexthop via ::ffff:5:7:6:4 weight 3 \
#                           nexthop via ::ffff:5:7:4:2 weight 1
#  # To Node 2
#  ip r add ::ffff:5:7:8:2 table 1 nexthop via ::ffff:5:7:1:3 weight 2 \
#                           nexthop via ::ffff:5:7:6:4 weight 3
#
#  # Through Node 1: from node 2
#  ip rule add prio 100 from ::ffff:5:7:8:2 table 2
#  # To Node 4
#  ip r add ::ffff:5:7:0:4 via ::ffff:5:7:6:4 table 2
#
#  # from node 3
#  ip rule add prio 100 from ::ffff:5:7:9:3 table 3
#  # To Node 2
#  ip r add ::ffff:5:7:8:2 via ::ffff:5:7:4:2 table 3
#  # To Node 4
#  ip r add ::ffff:5:7:0:4 table 3 nexthop via ::ffff:5:7:6:4 weight 3 \
#                           nexthop via ::ffff:5:7:4:2 weight 1
#
#  # from node 4
#  ip rule add prio 100 from ::ffff:5:7:0:4 table 4
#  # To Node 2:
#  ip r add ::ffff:5:7:8:2 via ::ffff:5:7:4:2 table 4
#  # to node 4:
#  ip r add ::ffff:5:7:9:3 via ::ffff:5:7:4:2 table 4
#
#EOF
#
#configure_node "ferma" <<EOF
#  # From Node 2
#  ip rule add prio 100 from ::ffff:5:7:8:2 table 2
#  # To node 1
#  ip r add ::ffff:5:7:7:1 table 2 nexthop via ::ffff:5:7:2:3 weight 3 \
#                           nexthop via ::ffff:5:7:5:4 weight 2
#  # To node 4
#  ip r add ::ffff:5:7:0:4 table 2 nexthop via ::ffff:5:7:4:1 weight 1 \
#                           nexthop via ::ffff:5:7:2:3 weight 3
#  # To node 3
#  ip r add ::ffff:5:7:9:3 table 2 nexthop via ::ffff:5:7:2:3 weight 3 \
#                           nexthop via ::ffff:5:7:4:1 weight 1 \
#                           nexthop via ::ffff:5:7:5:4 weight 2
#
#  # Through Node 2: from Node 1
#  ip rule add prio 100 from ::ffff:5:7:7:1 table 1
#  # to Node 4 
#  ip r add ::ffff:5:7:0:4 via ::ffff:5:7:5:4 table 1
#  # to Node 3 through node 3 or node 4
#  ip r add ::ffff:5:7:9:3 table 1 nexthop via ::ffff:5:7:2:3 weight 3 \
#                           nexthop via ::ffff:5:7:5:4 weight 2
#  #  from Node 4
#  ip rule add prio 100 from ::ffff:5:7:0:4 table 4
#  # to node 1:
#  ip r add ::ffff:5:7:7:1 via ::ffff:5:7:4:1 table 4
#  # to node 3:
#  ip r add ::ffff:5:7:9:3 via ::ffff:5:7:2:3 table 4
#
#  # from node 3
#  ip rule add prio 100 from ::ffff:5:7:9:3 table 3
#  # to node 1
#  ip r add ::ffff:5:7:7:1 via ::ffff:5:7:4:1 table 3
#  # to node 4
#  ip r add ::ffff:5:7:0:4 via ::ffff:5:7:5:4 table 3 
#
#EOF
#
#configure_node "rufus" <<EOF
#  # From Node 3
#  ip rule add prio 100 from ::ffff:5:7:9:3 table 3
#  # To Node 1:
#  ip r add ::ffff:5:7:7:1 table 3 nexthop via ::ffff:5:7:2:2 weight 3 \
#                                  nexthop via ::ffff:5:7:3:4 weight 1
#  # To Node 2:
#  ip r add ::ffff:5:7:8:2 table 3 nexthop via ::ffff:5:7:2:2 weight 3 \
#                                  nexthop via ::ffff:5:7:3:4 weight 1 \
#                                  nexthop via ::ffff:5:7:1:1 weight 2
#  # To Node 4:
#  ip r add ::ffff:5:7:0:4 table 3 nexthop via ::ffff:5:7:2:2 weight 3 \
#                                  nexthop via ::ffff:5:7:1:1 weight 2
#
#  # Through Node 3: from Node 1
#  ip rule add prio 100 from ::ffff:5:7:7:1 table 1
#  # To Node 4
#  ip r add ::ffff:5:7:0:4 via ::ffff:5:7:3:4 table 1
#  # To Node 2 or through node 4
#  ip r add ::ffff:5:7:8:2 table 1 nexthop via ::ffff:5:7:2:2 weight 3 \
#                                  nexthop via ::ffff:5:7:3:4 weight 1
#
#  # From Node 2
#  ip rule add prio 100 from ::ffff:5:7:8:2 table 2
#  # To Node 1:
#  ip r add ::ffff:5:7:7:1 via ::ffff:5:7:1:1 table 2
#  # To Node 4:
#  ip r add ::ffff:5:7:0:4 table 2 nexthop via ::ffff:5:7:3:4 weight 1 \
#                           nexthop via ::ffff:5:7:1:1 weight 2
#
#  # From Node 4
#  ip rule add prio 100 from ::ffff:5:7:0:4 table 4
#  # To Node 1:
#  ip r add ::ffff:5:7:7:1 via ::ffff:5:7:1:1 table 4
#  # To Node 2:
#  ip r add ::ffff:5:7:8:2 table 4 nexthop via ::ffff:5:7:2:2 weight 3 \
#                                  nexthop via ::ffff:5:7:1:1 weight 2
#EOF
#
#configure_node "kreia" <<EOF
#  # From Node 4
#  ip rule add prio 100 from ::ffff:5:7:0:4 table 4
#  # To Node 1
#  ip r a ::ffff:5:7:7:1 table 4 nexthop via ::ffff:5:7:6:1 weight 3 \
#                         nexthop via ::ffff:5:7:5:2 weight 2 \
#                         nexthop via ::ffff:5:7:3:3 weight 1
#  # To Node 2
#  ip r a ::ffff:5:7:8:2 table 4 nexthop via ::ffff:5:7:6:1 weight 3 \
#                         nexthop via ::ffff:5:7:3:3 weight 1
#  # To Node 3
#  ip r a ::ffff:5:7:9:3 table 4 nexthop via ::ffff:5:7:6:1 weight 3 \
#                         nexthop via ::ffff:5:7:5:2 weight 2 \
#                         nexthop via ::ffff:5:7:3:3 weight 1
#
#  # Through Node 4: from node 1
#  ip rule add prio 100 from ::ffff:5:7:7:1 table 1
#  # to Node 3
#  ip r add ::ffff:5:7:9:3 via ::ffff:5:7:3:3 table 1
#  # to Node 2
#  ip r add ::ffff:5:7:8:2 via ::ffff:5:7:5:2 table 1 
#
#  # from Node 2
#  ip rule add prio 100 from ::ffff:5:7:8:2 table 2
#  # To Node 1:
#  ip r add ::ffff:5:7:7:1 via ::ffff:5:7:6:1 table 2
#  # to node 3:
#  ip r add ::ffff:5:7:9:3 via ::ffff:5:7:3:3 table 2
#
#  # from node 3
#  ip rule add prio 100 from ::ffff:5:7:9:3 table 3
#  # to node 1
#  ip r add ::ffff:5:7:7:1 table 3 nexthop via ::ffff:5:7:6:1 weight 3 \
#                                  nexthop via ::ffff:5:7:5:2 weight 2
#  # to node 2
#  ip r add ::ffff:5:7:8:2 via ::ffff:5:7:5:2 table 3 
#EOF
