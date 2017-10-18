#include <systemc.h>

#include "timer.hpp"
#include "output_compare.hpp"
#include "bus.hpp"

SC_MODULE (test_bus) {
    sc_in_clk       clk;

    sc_signal<bool> rst, rd_i, wr_i, tm1_tm_of, tm2_tm_of,
                    tm1_rd_o, tm1_wr_o,
                    tm2_rd_o, tm2_wr_o,
                    oc_rd_o, oc_wr_o;

    sc_signal<uint32_t> addr_i, /* From master. */
                        data_i, /* From master. */
                        data_o, /* To master. */
                        tm1_addr_o, /* To timer 1. */
                        tm1_data_i, /* From timer 1.*/
                        tm2_addr_o, tm2_data_i,
                        oc_addr_o,  oc_data_i,
                        tm1_tval_o, tm2_tval_o;

 //   oc *oc1;
    timer *tm1;
    timer *tm2;
    bus *bs1;

    void test_write(mem_map addr, uint32_t val) {
        addr_i.write(addr);
        data_i.write(val);
        wr_i.write(true);
        wait();
        wr_i.write(false);
        wait();
    }

    void test_read(mem_map addr) {
        addr_i.write(addr);
        rd_i.write(true);
        wait();
        rd_i.write(false);
        wait();
        uint32_t tmp  = data_o.read();
        cout << "@" << sc_time_stamp() << " Test: read value: " << tmp << " addr: " << addr << endl;
    }

    void test_reset() {
        rst.write(true);
        wait();
        rst.write(false);
        wait();
    }

    void test() {
        test_reset();
        wait();

        test_write(mem_map::TVAL_TM1, 42);

        wait(2);

        test_write(mem_map::TVAL_TM2, 34);

        wait(2);

        test_read(mem_map::TVAL_TM1);

        wait(1);
        
        test_read(mem_map::TVAL_TM2);

        wait(10);
        sc_stop();
    }

    SC_CTOR(test_bus) {

        bs1 = new bus("bus1");
        bs1->clk_i(clk);
        bs1->rst_i(rst); 
        /* master */
        bs1->addr_i(addr_i);
        bs1->rd_i(rd_i);
        bs1->wr_i(wr_i);
        bs1->data_o(data_o);
        /* timer 1*/
        bs1->tm1_data_i(tm1_data_i);
        bs1->tm1_addr_o(tm1_addr_o);
        bs1->tm1_rd_o(tm1_rd_o);
        bs1->tm1_wr_o(tm1_wr_o);
        /* timer 1*/
        bs1->tm2_data_i(tm2_data_i); /* From slave. */
        bs1->tm2_addr_o(tm2_addr_o); /* To slave.   */
        bs1->tm2_rd_o(tm2_rd_o);
        bs1->tm2_wr_o(tm2_wr_o);
        /* timer 1*/
        bs1->oc_data_i(oc_data_i);
        bs1->oc_addr_o(oc_addr_o);
        bs1->oc_rd_o(oc_rd_o);
        bs1->oc_wr_o(oc_wr_o);

        tm1 = new timer("tm1");
        tm1->clk_i(clk);
        tm1->rst_i(rst);

        tm1->rd_i(tm1_rd_o);
        tm1->wr_i(tm1_wr_o);
        tm1->data_i(data_i);     /* From master. */
        tm1->data_o(tm1_data_i); /* To master.   */
        tm1->addr_i(tm1_addr_o);
        tm1->tval_o(tm1_tval_o);
        tm1->tm_of(tm1_tm_of);


        tm2 = new timer("tm2");
        tm2->clk_i(clk);
        tm2->rst_i(rst);

        tm2->rd_i(tm2_rd_o);
        tm2->wr_i(tm2_wr_o);
        tm2->data_i(data_i);
        tm2->data_o(tm2_data_i);
        tm2->addr_i(tm2_addr_o);
        tm2->tval_o(tm2_tval_o);
        tm2->tm_of(tm2_tm_of);

        SC_THREAD(test);
            sensitive << clk.pos();
//        oc1 = new oc("oc1");
//

//
//        oc1->clk_i(clk);
//        oc1->rst_i(rst);
//
//        oc1->rd_i(rd);
//        oc1->wr_i(wr);
//        oc1->data_i(data_i);
//        oc1->data_o(data_o);
//        oc1->addr_i(addr);
//        oc1->tms[0](tms_1);
//        oc1->tms[1](tms_2);
//        oc1->tms_overflow[0](tms_of_1);
//        oc1->tms_overflow[1](tms_of_2);
//        oc1->outs(outs);
//

//
    }
};

int 
sc_main(int argc, char *argv[]) {

    sc_clock clock("clk", sc_time(10, SC_NS));

    test_bus obj("test_bus");
    obj.clk(clock);

    sc_trace_file *wf = sc_create_vcd_trace_file("wave_bus");

    sc_trace(wf, obj.clk       , "clk"       );
    sc_trace(wf, obj.rst       , "rst"       ); 
    sc_trace(wf, obj.addr_i    , "addr_i"    );
    sc_trace(wf, obj.data_i    , "data_i"    );
    sc_trace(wf, obj.rd_i      , "rd_i"      );
    sc_trace(wf, obj.wr_i      , "wr_i"      );
    sc_trace(wf, obj.data_o    , "data_o"    );
    sc_trace(wf, obj.tm1_data_i, "tm1_data_i");
    sc_trace(wf, obj.tm1_addr_o, "tm1_addr_o");
    sc_trace(wf, obj.tm1_rd_o  , "tm1_rd_o"  );
    sc_trace(wf, obj.tm1_wr_o  , "tm1_wr_o"  );
    sc_trace(wf, obj.tm2_data_i, "tm2_data_i");
    sc_trace(wf, obj.tm2_addr_o, "tm2_addr_o");
    sc_trace(wf, obj.tm2_rd_o  , "tm2_rd_o"  );
    sc_trace(wf, obj.tm2_wr_o  , "tm2_wr_o"  );
    sc_trace(wf, obj.oc_data_i , "oc_data_i" );
    sc_trace(wf, obj.oc_addr_o , "oc_addr_o" );
    sc_trace(wf, obj.oc_rd_o   , "oc_rd_o"   );
    sc_trace(wf, obj.oc_wr_o   , "oc_wr_o"   );
    sc_trace(wf, obj.tm1_tm_of, "tm1_tm_of");
    sc_trace(wf, obj.tm2_tm_of, "tm2_tm_of");
    sc_trace(wf, obj.tm1_tval_o, "tm1_tval_o");
    sc_trace(wf, obj.tm2_tval_o, "tm2_tval_o");

    sc_start();

    sc_close_vcd_trace_file(wf);
    return 0;
}
