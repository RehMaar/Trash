#include "bus.hpp"

using namespace timer;
using namespace bus;
using namespace std;

pair<addr_t, slave_num>  bus::decode(mem_map addr) {
    switch (addr) {
        case TMR_TM1:
            return make_pair(reg_map_addr::TMR_ADDR, slave_num::TM1);
        case TVAL_TM1:
            return make_pair(reg_map_addr::TMR_ADDR, slave_num::TM1);
        case TCONF_TM1:
            return make_pair(reg_map_addr::TMR_ADDR, slave_num::TM1);
        case TMR_TM2:
            return make_pair(reg_map_addr::TMR_ADDR, slave_num::TM2);
        case TVAL_TM2:
            return make_pair(reg_map_addr::TMR_ADDR, slave_num::TM2);
        case TCONF_TM2:
            return make_pair(reg_map_addr::TMR_ADDR, slave_num::TM2);
        case OCCONF_OC:
            return make_pair(oc::reg_map_addr::OCCONF_ADDR, slave_num::OC);
        case OCR_OC:
            return make_pair(oc::reg_map_addr::OCR_ADDR, slave_num::OC);
    }
    return make_pair((addr_t)0, (slave_num)0);
}

uint32_t bus::channel_switch() {
    /* Decode address. */
    pair<addr_t, slave_num> p = decode((mem_map)addr_i.read());

    slave_signals ss = channels[p.second]

    ss.addr_o.write(p.first); 
    data_o.write(ss.data_i.read());
    ss.rd_o.write(rd_i.read());
    ss.wr_o.write(wr_i.read();

}
