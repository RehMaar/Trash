#include "timer.hpp"

sc_uint<32> *timer::get_register(uint32_t addr) {
    return reg_map[addr < REG_NUM ? addr : 0];
}

void timer::count() {
    if (tconf[RUN_BIT]) {
        if (tconf[TYPE_BIT] == INC) {
            tval = tval == tmr ? 0 : tval + 1;
        } else {
            tval = tval == 0 ? tmr : sc_uint<32>(tval - 1);
        }
    }
}

void timer::reset() {
    tmr   = 0;
    tval  = 0;
    tconf = 0;
}

void timer::read() {
    if (rd_i) {
        data_o.write(* get_register(addr_i.read()) );
    }
}

void timer::write() {
    if (wr_i) {
        sc_uint<32> *reg = get_register(addr_i.read());
        *reg = data_i.read();
    }
}
