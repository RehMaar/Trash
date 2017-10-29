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

void cpu::set_timer(mem_map addr, timer::timer_mode m, timer::timer_mode t) {
    sc_uint<32> val = 0;
    val[timer::timer_mode::RUN_BIT]  = m;
    val[timer::timer_mode::TYPE_BIT] = t;
    write_reg(addr, (uint32_t)val);
}

void cpu::generate_signal() {
    /* To generate signal with w == 1 it's possible just to use
     * one of the OC modes.*/
    if (w == 1) {
        generate_signal_simple();
    } else {
        generate_signal_long(w);
    }
    sc_stop();
}

#define DEBUG_COUNT_INIT(c_) uint32_t count = c_;
#define DEBUG_COUNT_DECR(v_) \
    {if (count == 0) { break; } else {count -= v_;} }

void cpu::generate_signal_simple() {
    DEBUG_COUNT_INIT(100);

    write_reg(mem_map::OCR_OC, 2);
    write_reg(mem_map::TMR_TM1, 2);

    set_oc(oc::oc_mode::SIMPLE_TO_ZERO, oc::oc_timer::TIMER1);

    set_timer(mem_map::TCONF_TM1, timer::timer_mode::RUN,
              timer::timer_mode::DEC);

    while (true) { 
        DEBUG_COUNT_DECR(1);
        wait();
    }
}

void cpu::generate_signal_long(uint32_t width)  {

    DEBUG_COUNT_INIT(100);
    /* */
    uint32_t period = width - 1;
    uint32_t triple_period = (width * 3) - 1;

    /* Set timers TMR. */
    write_reg(mem_map::TMR_TM1, period);
    write_reg(mem_map::TMR_TM2, triple_period);

    /* Set output_compare OCR. */
    write_reg(mem_map::OCR_OC, 0);

    /* Set OC's working timer1. */
    set_oc(oc::oc_mode::TOGGLE, oc::oc_timer::TIMER2);

    /* Set timer configuration and run timer 2. */
    set_timer(mem_map::TCONF_TM2, timer::timer_mode::RUN,
              timer::timer_mode::DEC);

    /* Run timer 1. Need to synchronize timers. */
    uint32_t j = 0;
    while (true) {
        if (j == period - 1) {
            set_timer(mem_map::TCONF_TM1, timer::timer_mode::RUN,
                      timer::timer_mode::DEC);
        } else if (j == triple_period - 2) {
            break;
        }
        j++;
        wait();
    }

    /* Here both TMRs is 0. */
    /* Duration of the seq. */
    uint32_t i = 0;

    /* Set moments when we need to switch timers.
     * The case when w == 2 is a special one because
     * of the time duration of data writing.
     */
    uint32_t first_switch  = width == 2 ? 2 : 2 * width - 3;
    uint32_t second_switch = width == 2 ? 2 : 3 * width - 4;

    while (true) {
        if (i == first_switch) {
            set_oc(oc::oc_mode::TOGGLE, oc::oc_timer::TIMER1);
        }
        if (i == second_switch) {
            set_oc(oc::oc_mode::TOGGLE, oc::oc_timer::TIMER2);
            i = 1;
            goto cont;
        }
        i++;
cont: 
        DEBUG_COUNT_DECR(1);
        wait();
    } 
}
#undef DEBUG_COUNT_INIT
#undef DEBUG_COUNT_DECR
