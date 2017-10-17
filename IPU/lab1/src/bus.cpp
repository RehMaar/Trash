#include <stdio.h>
#include "bus.hpp"

using namespace std;

bus::bus(sc_module_name nm) : sc_module(nm) {
    SC_METHOD(channel_switch)
        sensitive << rd_i << wr_i;
}

pair<addr_t, bus::slave_addr>  bus::decode(mem_map addr) {
    switch (addr) {     
        case TMR_TM1:
            return make_pair(timer::timer_reg_map::TMR_ADDR, bus::slave_addr::TM1);
        case TVAL_TM1:
            return make_pair(timer::timer_reg_map::TVAL_ADDR, bus::slave_addr::TM1);
        case TCONF_TM1:
            return make_pair(timer::timer_reg_map::TCONF_ADDR, bus::slave_addr::TM1);
        case TMR_TM2:
            return make_pair(timer::timer_reg_map::TMR_ADDR, bus::slave_addr::TM2);
        case TVAL_TM2:
            return make_pair(timer::timer_reg_map::TVAL_ADDR, bus::slave_addr::TM2);
        case TCONF_TM2:
            return make_pair(timer::timer_reg_map::TCONF_ADDR, bus::slave_addr::TM2);
        case OCCONF_OC:
            return make_pair(oc::oc_reg_map::OCCONF_ADDR, bus::slave_addr::OC);
        case OCR_OC:
            return make_pair(oc::oc_reg_map::OCR_ADDR, bus::slave_addr::OC);
    }
    return make_pair((addr_t)0, (bus::slave_addr)0);
}

void bus::channel_switch() {
    /* Decode address. */
    pair<addr_t, bus::slave_addr> p = bus::decode((mem_map)addr_i.read());
    bus::slave_signals ss = channels[p.second];

    /* Set local addres. */
    (*ss.addr_o).write(p.first);
    /* Write data to output. WTF? */
    data_o.write((*ss.data_i).read());
    /* Send signals to the slave.*/
    (*ss.rd_o).write(rd_i.read());
    (*ss.wr_o).write(wr_i.read());
}
