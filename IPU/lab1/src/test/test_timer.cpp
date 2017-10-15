#include <systemc.h>
#include "timer.hpp"

SC_MODULE (test_timer) {
    sc_in_clk clk;

    sc_signal<bool> reset, rd, wr;
    sc_signal<sc_uint<32>> data_i, data_o, addr, tval_o;

    timer *timer1;

private:

    void write_register(timer::timer_reg_map reg, sc_uint<32> val) {
        addr.write(reg);
        data_i.write(val);
        wr.write(true);
        wait();
        wr.write(false);
        wait();
    }

    sc_uint<32> read_register(timer::timer_reg_map reg) {
        addr.write(reg);
        rd.write(true);
        wait();
        rd.write(false);
        wait();
        sc_uint<32> val = data_o.read();
        return val;
    }

    void test_reset() {
        wait();
        reset.write(true);
        wait();
        reset.write(false);
        wait();
    }

    void test_set_tmr(uint32_t tmr) {
        cout << "Test: set value: " << tmr << endl;
        write_register(timer::timer_reg_map::TMR_ADDR, tmr);
        sc_uint<32> val = read_register(timer::timer_reg_map::TMR_ADDR);
        cout << "Test: read after setting TMR: " <<  val << endl;
    }
    
    void test_overflow() {
        cout << "Test: " << __FUNCTION__ << "()" << endl;
    }

    void test_conf(timer::timer_mode run, timer::timer_mode type) {
        sc_uint<32> val = read_register(timer::timer_reg_map::TCONF_ADDR);
        cout << "Test: read tconf: " << val << endl;

        val[timer::timer_mode::RUN_BIT]  = run;
        val[timer::timer_mode::TYPE_BIT] = type;

        cout << "Test: set time in run mode: " << val << endl;

        write_register(timer::timer_reg_map::TCONF_ADDR, val);
        cout << "Test: write tconf" << endl;

        val = read_register(timer::timer_reg_map::TCONF_ADDR);
        cout << "Test: read tconf: " << val << endl;
    }

    void test_read_val() {
        sc_uint<32> val = read_register(timer::timer_reg_map::TVAL_ADDR);
        cout << "Test: tval: " << val << endl;
    }

public:
    void test() {
        cout << ">>> Test: reset timer." << endl;
        test_reset();
        wait();

        cout << ">>> Test: set TMR" << endl;
        test_set_tmr(100);

        cout << ">>> Test: set RUN on increment timer" << endl;
        test_conf(timer::timer_mode::RUN, timer::timer_mode::INC);
        test_read_val();
        test_read_val();

        cout << ">>> Test: set STOP" << endl;
        test_conf(timer::timer_mode::STOP, timer::timer_mode::INC);
        test_read_val();
        test_read_val();

        cout << ">>> Test: set RUN on decrement timer" << endl;
        test_conf(timer::timer_mode::RUN, timer::timer_mode::DEC);
        test_read_val();
        test_read_val();

        cout << ">>> Test: set STOP" << endl;
        test_conf(timer::timer_mode::STOP, timer::timer_mode::INC);
        test_read_val();
        test_read_val();

        cout << ">>> Test: overflow decrement timer" << endl;
        cout << "Test: set TVAL to zero" << endl;
        write_register(timer::timer_reg_map::TVAL_ADDR, 0);
        test_read_val();

        test_conf(timer::timer_mode::RUN, timer::timer_mode::DEC);
        test_read_val();
        test_read_val();

        cout << ">>> Test: stop timer" << endl;
        test_conf(timer::timer_mode::STOP, timer::timer_mode::INC);
        test_read_val();
        test_read_val();

        cout << ">>> Test: overflow increment timer" << endl;
        cout << "Test: set TVAL to TMR" << endl;
        write_register(timer::timer_reg_map::TVAL_ADDR, 100);
        test_read_val();

        test_conf(timer::timer_mode::RUN, timer::timer_mode::INC);
        test_read_val();
        test_read_val();

        cout << ">>> Test: stop timer" << endl;
        test_conf(timer::timer_mode::STOP, timer::timer_mode::INC);
        test_read_val();
        test_read_val();

        wait(10);
        sc_stop();
    }

    void read_value () {
        cout << "Test: read tval: " << tval_o.read() << endl;
    }

    SC_CTOR (test_timer) {
        timer1 = new timer("timer1");
        timer1->clk_i (clk);
        timer1->rst_i (reset);
        timer1->rd_i  (rd);
        timer1->wr_i  (wr);
        timer1->data_i(data_i);
        timer1->data_o(data_o);
        timer1->addr_i(addr);
        timer1->tval_o(tval_o);

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
    sc_trace(wf, obj.clk   , "clk"   );
    sc_trace(wf, obj.reset , "reset" );
    sc_trace(wf, obj.data_i, "data_i");
    sc_trace(wf, obj.data_o, "data_o");
    sc_trace(wf, obj.addr  , "addr"  );
    sc_trace(wf, obj.wr    , "wr"    );
    sc_trace(wf, obj.rd    , "rd"    );
    sc_trace(wf, obj.tval_o, "tval_o");

    sc_start();

    sc_close_vcd_trace_file(wf);

    return 0;
}
