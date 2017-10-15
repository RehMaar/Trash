#include "output_compare.hpp"

oc::oc(sc_module_name nm) : sc_module(nm) {
    /* Base operations. */
    SC_METHOD (reset);
        sensitive << rst_i;
    SC_METHOD (read);
        sensitive << clk_i.pos();
    SC_METHOD (write);
        sensitive << clk_i.pos();
    SC_METHOD (set_new_mode);
        sensitive << occonf;
    SC_METHOD (out_logic);
        sensitive << clk_i.pos();
}

sc_uint<32> *oc::get_register(uint32_t addr) {
    return reg_map[addr < REG_NUM ? addr : 0];
}

/**
 * Reset registers.
 */
void oc::reset() {
    simple_mode = false;
    pwm_mode    = false;
    logic_rst   = false;

    occonf = 0;
    ocr    = 0;
}

/**
 * Read data from `addr_i' register to `data_o'.
 */
void oc::read() {
    if (rd_i) {
        data_o.write(* get_register(addr_i.read()) );
    }
}

/**
 * Write data from `data_i' to `addr_i' register.
 */
void oc::write() {
    if (wr_i) {
        sc_uint<32> *reg = get_register(addr_i.read());
        *reg = data_i.read();
    }
}

/**
 * Compare OCR value with chosen timer.
 */
bool oc::cmp_ocr() {  
    return ocr == tms[occonf[oc_conf::TM_WRK]].read();
}

/**
 * Detect currenct OC mode and set internal configuration for it.
 */
void set_new_mode() {
    simple_mode = false;
    pwm_mode    = false;
    switch (occonf.range(oc::oc_conf::OC_MODE_START,
                         oc::oc_conf::OC_MODE_END)) {
        case OFF: {
            return;
        }
        case SIMPLE_TO_ONE: {
            logic_rst = false;
            simple_mode = true;
            break;
        }
        case SIMPLE_TO_ZERO: {
            logic_rst = true;
            simple_mode = true;
            break;
        }
        case TOGGLE: {
            outs.write(!outs.read());
            return;
        }
        case PWM_TO_ONE: {
            logic_rst = false;
            pwm_mode = true;
            break;
        }
        case PWM_TO_ZERO: {
            logic_rst = true;
            pwn_mode = true;
            break;
        }
    }
    outs.write(logic_rst);
}

void oc::out_logic() {
    if (simple_mode) {
        if (cmp_ocr()) {
            outs.write(!logic_rst);
        } else {
            outs.write(logic_rst); 
        }
    } else if (pwm_mode) {
        if (cmp_ocr()) {
            if (tms_overflow[occonf[oc_conf::TM_WRK]].read()) {
                outs.write(logic_rst);
            } else {
                outs.write(!logic_rst);
            }
        } else {
            outs.write(logic_rst);
        }
    }
}
