#include <systemc.h>
#include "timer.hpp"

SC_MODULE (test_timer) {
    sc_in_clk clk;

    sc_signal<bool> reset, rd, wr;
    sc_signal<uint32_t> data_i, data_o, addr;

    timer *timer1;

private:

    void check_register(timer::reg_map_addr reg) {
        addr.write(reg);
        rd.write(true);
        wait();
        rd.write(false);
        wait();
        uint32_t val = data_o.read();
        cout << "reg value: " << val << endl;
    }

    void test_reset() {
        wait();
        reset.write(true);
        wait();
        reset.write(false);
        wait();
        cout << "Test: register TMR" << endl;
        check_register(timer::reg_map_addr::TMR_ADDR);
        cout << "Test: register TVAL" << endl;
        check_register(timer::reg_map_addr::TVAL_ADDR);
        cout << "Test: register TCONF" << endl;
        check_register(timer::reg_map_addr::TCONF_ADDR);
    }

    void test_decr () {
    }


    void test_incr () {
    }


    void test_decr_stop () {
        cout << "Test: " << __FUNCTION__ << endl;
    }

    void test_incr_stop () {
        cout << "Test: " << __FUNCTION__ << endl;
    }

    void test_overflow() {
        cout << "Test: " << __FUNCTION__ << "()" << endl;
    }

    void test_run() {
        timer::run_timer()
    }

public:
    void test() {
        cout << "Test: reset timer." << endl;
        test_reset();
        wait();

        cout << "Test: set RUN" << endl;
        test_run();

//        cout << "Test: decriment when STOP." << endl;
//        test_decr_stop();
//        wait(); 
//        cout << "Test: increment when STOP." << endl;
//        test_incr_stop();
//        wait();
//        cout << "Test: decriment." << endl;
//        test_decr();
//        wait(); 
//        cout << "Test: increment." << endl;
//        test_incr();
//        wait();
//        cout << "Test: check overflow." << endl;
//        test_overflow();

        wait(10);
        sc_stop();
    }

    SC_CTOR (test_timer) {
        timer1 = new timer("timer1");
        timer1->clk_i (clk);
        timer1->rst_i (reset);
        timer1->rd_i (rd);
        timer1->wr_i (wr);
        timer1->data_i(data_i);
        timer1->data_o(data_o);
        timer1->addr_i(addr);

        SC_THREAD (test);
            sensitive << clk.pos();
    }
    
};

int
sc_main(int argc, char *argv[]) {

    sc_clock clock("clk", sc_time(10, SC_NS));

    test_timer obj("test_timer");
    obj.clk(clock);

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
