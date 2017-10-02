#include <systemc.h>
#include "timer.hpp"

SC_MODULE (test_timer) {
    sc_in_clk clk;

    sc_signal<bool> reset, rd, wr;
    sc_signal<uint32_t> data_i, data_o, addr;
    timer *timer1;

    void test() {
        cout << "Test!" << endl;
    }

    SC_CTOR (test_timer) {
        timer1 = new timer("timer1");
        timer1->clk_i (clk);
        timer1->rst_i (reset);
        timer1->rd_i (rd);
        timer1->wr_i (wr);
        timer1->data_i(data_i);
        timer1->data_o(data_o);

        SC_THREAD (test);
            sensitive << clk.pos();
    }
    
};

int sc_main() {

    sc_clock clock("clk", sc_time(10, SC_NS));

    test_timer obj("test_timer");

    sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    sc_trace(wf, obj.clk, "clk");
    sc_trace(wf, obj.reset, "reset");
    sc_trace(wf, obj.data_i, "data_i");
    sc_trace(wf, obj.data_o, "data_o");
    sc_trace(wf, obj.addr, "addr");
    sc_trace(wf, obj.wr, "wr");
    sc_trace(wf, obj.rd, "rd");

    sc_start();

    sc_close_vcd_trace_file(wf);

    return 0;
}
