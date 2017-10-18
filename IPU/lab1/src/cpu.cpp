#include "cpu.hpp"
#include "timer.hpp"
#include "mem_map.hpp"
#include "output_compare.hpp"
#include "bus.hpp"

void cpu::write(mem_map addr, uint32_t val) {
    addr_o.write(addr);
    data_o.write(val);
    wr_o.write(true);
    wait();
    wr_o.write(false);
}

uint32_t cpu::read(mem_map addr) {
    return 0;
}

void cpu::generate_signal() {
    int count = 50; 
    uint32_t i = 0;
    fsm_state state = SET_OC;
    while (count) {
        switch (state) {
            case SET_OC: {
                //cout << "@ " << sc_time_stamp() << "CPU: SET_OC" << endl;
                sc_uint<32> val = 0;
                val.range(oc::oc_conf::OC_MODE_END, oc::oc_conf::OC_MODE_START)
                    = oc::oc_mode::SIMPLE_TO_ZERO;
                write(mem_map::OCCONF_OC, (uint32_t)val);
                state = SET_TIMER;
                break;
            }
            case SET_TIMER: {
                //cout << "@ " << sc_time_stamp() << "CPU: SET_TIMER" << endl;
                sc_uint<32> val = 0;
                val[timer::timer_mode::RUN_BIT] = timer::timer_mode::RUN;
                write(mem_map::TCONF_TM1, val);
                write(mem_map::TMR_TM1, w);
                state = FIRST_SIGNAL;
                break;
            }
            case FIRST_SIGNAL: {
                //cout << "@ " << sc_time_stamp() << "CPU: FIRST_SIGNAL" << endl;
                if (i != w) {
                    i++;
                } else {
                    state = SECOND_SIGNAL;
                    i = 0;
                }
                break;
            }
            case SECOND_SIGNAL: {
                //cout << "@ " << sc_time_stamp() << "CPU: SECOND_SIGNAL" << endl;
                if (i != w) {
                    i++;
                } else {
                    state = THIRD_SIGNAL;
                    i = 0;
                }
                break;
            }
            case THIRD_SIGNAL: {
                //cout << "@ " << sc_time_stamp() << "CPU: THIRD_SIGNAL" << endl;
                if (i != w) {
                    i++;
                } else {
                    state = FIRST_SIGNAL;
                    i = 0;
                }
                break;
            }
        }
        count--;
        wait();
    }
    sc_stop();
}
