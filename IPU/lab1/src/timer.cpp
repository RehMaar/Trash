#include "timer.hpp"

timer::timer(sc_module_name nm) : sc_module(nm) {
    /* Public methods. */
    SC_METHOD (reset);
        sensitive << rst_i;
    SC_METHOD (read);
        sensitive << clk_i.pos();
    SC_METHOD (write);
        sensitive << clk_i.pos();
    /* Private methods. */
    SC_METHOD (count);
    sensitive << clk_i.pos();
}

sc_uint<32> *timer::get_register(uint32_t addr) {
    return reg_map[addr < REG_NUM ? addr : 0];
}

void timer::count() {
    if (tconf[RUN_BIT]) {
        cout << sc_time_stamp() << " Timer: count" << endl;
        if (tconf[TYPE_BIT] == INC) {
            tm_of.write(tval == tmr);
            tval = tval == tmr ? 0 : tval + 1;
        } else {
            tm_of.write(tval == 0);
            tval = tval == 0 ? tmr : sc_uint<32>(tval - 1);
        }
    } else {
        tm_of.write(false);
    }
    tval_o.write(tval);
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
