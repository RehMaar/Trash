#include "cpu.hpp"
#include "timer.hpp"
#include "mem_map.hpp"
#include "output_compare.hpp"
#include "bus.hpp"

void cpu::write_reg(mem_map addr, uint32_t val) {
    addr_o.write(addr);
    data_o.write(val);
    wr_o.write(true);
    wait();
    wr_o.write(false);
    wait();
}

void cpu::set_oc(oc::oc_mode mode, oc::oc_timer tm)  {
    sc_uint<32> conf = 0;
    conf[oc::oc_conf::TM_WRK] = tm;
    conf.range(oc::oc_conf::OC_MODE_END, oc::oc_conf::OC_MODE_START) = mode;
    write_reg(mem_map::OCCONF_OC, conf);
}

void cpu::generate_signal() {

    uint32_t count = 100; /* To get wave. */
    /* */
    uint32_t period = w - 1;
    uint32_t triple_period = (w * 3) - 1;
    /* Set timers TMR. */
    write_reg(mem_map::TMR_TM1, period);
    write_reg(mem_map::TMR_TM2, triple_period);
    /* Set output_compare OCR. */
    write_reg(mem_map::OCR_OC, 0);
    /* Set OC's working timer1 and decrement more. */
    set_oc(oc::oc_mode::TOGGLE, oc::oc_timer::TIMER2);
    /* Set timer configuration. */
    sc_uint<32> val = 0;
    val[timer::timer_mode::RUN_BIT]  = timer::timer_mode::RUN;
    val[timer::timer_mode::TYPE_BIT] = timer::timer_mode::DEC;
    /* Run timer 2. */
    write_reg(mem_map::TCONF_TM2, (uint32_t)val);
    /* Run timer 1. Need to synchronize timers. */
    uint32_t j = 0;
    while (true) {
        if (j == period - 1) {
            write_reg(mem_map::TCONF_TM1, (uint32_t)val);
        } else if (j == triple_period - 1) {
            break;
        }
        j++;
        wait();
    }

    fsm_state state = FIRST_SIGNAL;
    uint32_t i = 0;
    while (true) {
        switch (state) {
            case FIRST_SIGNAL: {
                if (i == period + 2) {
                    set_oc(oc::oc_mode::TOGGLE, oc::oc_timer::TIMER1);
                    state = SECOND_SIGNAL;
                   i = 0;
                   break;
                }
                i++;
                break;
            }
            case SECOND_SIGNAL: {
                if (i == 1) {
                    set_oc(oc::oc_mode::TOGGLE, oc::oc_timer::TIMER2);
                    state = FIRST_SIGNAL;
                    i = 0;
                    break;
                }
                i++;
                break;
            }
        }
        if (count == 0)
            break;
        count--;
        wait();
    } 
    sc_stop();
}
