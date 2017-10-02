#include "timer.hpp"

void timer::count() {
    if (IS_RUN(tconf)) {
        if (IS_INC_MODE(tconf)) {
            tval = tval == tmr ? 0 : tval + 1;
        } else {
            tval = tval == 0 ? tmr : tval - 1;
        }
    }
}

void timer::reset() {
    tmr = 0;
    tval = 0;
    tconf = 0;
}

void timer::read() {
    if (rd_i) {
        data_o.write(tmr);
    }
}

void timer::write() {
    if (wr_i) {
        tmr = data_i.read();
    }
}

