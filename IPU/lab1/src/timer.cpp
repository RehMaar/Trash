#include "timer.hpp"

uint32_t *timer::get_register(uint32_t addr) {
    return reg_map[addr < REG_NUM ? addr : 0];
}

void timer::count() {
    if (READ_BIT(tconf, RUN_BIT)) {
        if (READ_BIT(tconf, TYPE_BIT) == INC) {
            tval = tval == tmr ? 0 : tval + 1;
        } else {
            tval = tval == 0 ? tmr : tval - 1;
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
        uint32_t *reg = get_register(addr_i.read());
        *reg = data_i.read();
    }
}
