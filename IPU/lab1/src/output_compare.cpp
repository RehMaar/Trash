#include "output_compare.hpp"

oc::oc(sc_module_name nm) : sc_module(nm) {
    /* Base operations. */
    SC_METHOD (reset);
        sensitive << rst_i;
    SC_METHOD (out_logic);
        sensitive << tms[0] << tms[1];
    SC_METHOD (read);
        sensitive << clk_i.pos();
    SC_METHOD (write);
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
        switch (addr_i.read()) {
            case OCCONF_ADDR: {
                occonf = data_i.read();
                set_new_mode();
                break;
            }
            case OCR_ADDR: {
                ocr = data_i.read();
                break;
            }
        }
    }
}

/**
 * Detect currenct OC mode and set internal configuration for it.
 */
void oc::set_new_mode() {
    simple_mode = false;
    pwm_mode    = false;
    toggle_mode = false;

    switch (occonf.range(2,0)) {
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
            toggle_mode = true;
            return;
        }
        case PWM_TO_ONE: {
            logic_rst = false;
            pwm_mode = true;
            break;
        }
        case PWM_TO_ZERO: {
            logic_rst = true;
            pwm_mode = true;
            break;
        }
    }
}

void oc::out_logic() {
    bool eq = ocr == tms[occonf[oc_conf::TM_WRK]].read();
    if (toggle_mode) {
        if (eq)
            outs.write(!outs.read());
    } else if (simple_mode) {
        outs.write(logic_rst ^ eq);
    } else if (pwm_mode) {
        bool tm_wrk = tms_overflow[occonf[oc_conf::TM_WRK]].read();
        if (eq && !tm_wrk) {
            outs.write(!logic_rst);
        } else {
            outs.write(logic_rst);
        }
    }
}
