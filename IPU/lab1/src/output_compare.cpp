#include "output_compare.hpp"

oc::oc(sc_module_name nm) : sc_module(nm) {
    SC_METHOD (reset);
        sensitive << rst_i;
    SC_METHOD (read);
        sensitive << clk_i.pos();
    SC_METHOD (write);
        sensitive << clk_i.pos();
    SC_METHOF (cmp_ocr);
        sensitive << tms;
}

sc_uint<32> *oc::get_register(uint32_t addr) {
    return reg_map[addr < REG_NUM ? addr : 0];
}

void oc::reset() {
    occonf = 0;
    ocr    = 0;
}

void oc::read() {
    if (rd_i) {
        data_o.write(* get_register(addr_i.read()) );
    }
}

void oc::write() {
    if (wr_i) {
        sc_uint<32> *reg = get_register(addr_i.read());
        *reg = data_i.read();
    }
}

bool oc::cmp_ocr() {  
    return ocr == tms[occonf[oc_conf::TM_WRK]].read();
}

void out_logic() {
    switch (occonf.range(oc::oc_conf::OC_MODE_START, oc::oc_conf::OC_MODE_END)) {
        case OFF: {
            return;
        }
        case TO_ONE: {
            outs_reg = false;
            /* If ocr == tm then outs(true) */
            break;
        }
        case TO_ZERO: {
            outs_reg = true;
            /* If ocr == tm then outs(false) */
            break;
        }
        case TOGGLE: {
            outs_reg = !outs_reg;
            break;
        }
        case PWM_TO_ONE: {
            outs_reg = false;
            /* if ocr == tm then outs(true); if overflow then outs(false)*/
            break;
        }
        case PWM_TO_ZERO: {
            outs_reg = true;
            /* if ocr == tm then outs(false); if overflow then outs(true)*/
            break;
        }
    }
}
