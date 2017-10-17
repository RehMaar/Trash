#include <systemc.h>

#include "timer.hpp"
#include "output_compare.hpp"

SC_MODULE (test_oc) {
    sc_in_clk       clk;

    sc_signal<bool> outs, rst, rd, wr, rd_tm, wr_tm, tms_of_1, tms_of_2;
    sc_signal<uint32_t> addr, data_i, data_o, tms_1, tms_2, addr_tm, data_i_tm, data_o_tm;

    oc *oc1;
    timer *tm;

    void write_register(uint32_t reg, sc_uint<32> val) {
        addr.write(reg);
        data_i.write(val);
        wr.write(true);
        wait();
        wr.write(false);
        wait();
    }

    void write_register_tm(uint32_t reg, sc_uint<32> val) {
        addr_tm.write(reg);
        data_i_tm.write(val);
        wr_tm.write(true);
        wait();
        wr_tm.write(false);
    }

    sc_uint<32> read_register(uint32_t reg) {
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
        rst.write(true);
        wait();
        rst.write(false);
        wait();
    }

    void test_set_mode1(uint32_t ocr) {
        write_register(oc::oc_reg_map::OCR_ADDR, ocr);
        sc_uint<32> val = 0;
        val = oc::oc_mode::SIMPLE_TO_ONE;
        write_register( oc::oc_reg_map::OCCONF_ADDR, val);
    }

    void set_timer1(uint32_t val) {
        write_register_tm(timer::timer_reg_map::TMR_ADDR, val);
        sc_uint<32> conf = 0;
        conf[timer::timer_mode::RUN_BIT] = timer::timer_mode::RUN;
        write_register_tm(timer::timer_reg_map::TCONF_ADDR, conf);
    }

    void test_set_mode2(uint32_t ocr) {
        write_register(oc::oc_reg_map::OCR_ADDR, ocr);
        sc_uint<32> val = 0;
        val = oc::oc_mode::SIMPLE_TO_ZERO;
        write_register( oc::oc_reg_map::OCCONF_ADDR, val);
    }

    void test_set_mode3(uint32_t ocr) {
        write_register(oc::oc_reg_map::OCR_ADDR, ocr);
        sc_uint<32> val = 0;
        val = oc::oc_mode::TOGGLE;
        write_register( oc::oc_reg_map::OCCONF_ADDR, val);
    }

    void test_set_mode4(uint32_t ocr) {
        write_register(oc::oc_reg_map::OCR_ADDR, ocr);
        sc_uint<32> val = 0;
        val = oc::oc_mode::PWM_TO_ONE;
        write_register( oc::oc_reg_map::OCCONF_ADDR, val);
    }

    void test_set_mode5(uint32_t ocr) {
        write_register(oc::oc_reg_map::OCR_ADDR, ocr);
        sc_uint<32> val = 0;
        val = oc::oc_mode::PWM_TO_ZERO;
        write_register( oc::oc_reg_map::OCCONF_ADDR, val);
    }

    void test() {
        test_reset();
        set_timer1(5);
        test_set_mode1(3);
        wait(10);

        test_reset();
        set_timer1(5);
        test_set_mode2(3);
        wait(10);

        test_reset();
        set_timer1(3);
        test_set_mode3(2);
        wait(20);

        test_reset();
        set_timer1(5);
        test_set_mode4(0);
        wait(20);

        test_reset();
        set_timer1(5);
        test_set_mode5(4);
        wait(20);

        sc_stop();
    }

    SC_CTOR(test_oc) {
        oc1 = new oc("oc1");
        oc1->clk_i(clk);
        oc1->rst_i(rst);

        oc1->rd_i(rd);
        oc1->wr_i(wr);
        oc1->data_i(data_i);
        oc1->data_o(data_o);
        oc1->addr_i(addr);
        oc1->tms[0](tms_1);
        oc1->tms[1](tms_2);
        oc1->tms_overflow[0](tms_of_1);
        oc1->tms_overflow[1](tms_of_2);
        oc1->outs(outs);

        tm = new timer("timer1");
        tm->clk_i(clk);
        tm->rst_i(rst);
        tm->rd_i(rd_tm);
        tm->wr_i(wr_tm);
        tm->data_i(data_i_tm);
        tm->data_o(data_o_tm);
        tm->addr_i(addr_tm);
        tm->tval_o(tms_1);
        tm->tm_of(tms_of_1);

        SC_THREAD (test);
            sensitive << clk.pos();
    }
};

int 
sc_main(int argc, char *argv[]) {

    sc_clock clock("clk", sc_time(10, SC_NS));

    test_oc obj("test_oc");
    obj.clk(clock);

    sc_trace_file *wf = sc_create_vcd_trace_file("wave");

    sc_trace(wf, obj.clk, "clk");
    sc_trace(wf, obj.rst, "rst");
    sc_trace(wf, obj.data_i, "data_i");
    sc_trace(wf, obj.data_o, "data_o");
    sc_trace(wf, obj.addr, "addr");
    sc_trace(wf, obj.rd, "rd");
    sc_trace(wf, obj.wr, "wr");
    sc_trace(wf, obj.outs, "outs");
    sc_trace(wf, obj.tms_1, "tms_1");
    sc_trace(wf, obj.tms_of_1, "tms_of_1");
    sc_trace(wf, obj.tms_2, "tms_2");
    sc_trace(wf, obj.tms_of_2, "tms_of_2");

    sc_start();

    sc_close_vcd_trace_file(wf);
    return 0;
}
