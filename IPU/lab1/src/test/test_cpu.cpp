#include <stdlib.h>
#include <systemc.h>

#include "cpu.hpp"

int sc_main(int argc, char * argv[]) {

    int i = 4;

    if (argc > 1) {
        i = atoi(argv[1]);
    }

    cout << "Duration: " << i << endl;
    
    sc_clock clock("clk", sc_time(10, SC_NS));

    sc_signal<uint32_t> data_i, data_o, addr_o;
    sc_signal<bool> wr_o, rd_o, rst;

    sc_signal<uint32_t> tm1_data_i, tm1_addr_o, tm1_val;
    sc_signal<bool> tm1_rd_o, tm1_wr_o, tm1_of;

    sc_signal<uint32_t> tm2_data_i, tm2_addr_o, tm2_val;
    sc_signal<bool> tm2_rd_o, tm2_wr_o, tm2_of;

    sc_signal<uint32_t> oc_data_i, oc_addr_o;
    sc_signal<bool> oc_rd_o, oc_wr_o, outs;

    cpu obj("cpu", i);
    obj.clk_i(clock);
    obj.data_i(data_i);
    obj.data_o(data_o);
    obj.addr_o(addr_o);
    obj.wr_o(wr_o);
    obj.rd_o(rd_o);

    bus bus1("bus1");
    bus1.clk_i(clock);
    bus1.rst_i(rst);
    /* master */
    bus1.addr_i(addr_o);
    bus1.rd_i(rd_o);
    bus1.wr_i(wr_o);
    bus1.data_o(data_i);
    /* Slaves. */
    bus1.tm1_data_i(tm1_data_i);
    bus1.tm2_data_i(tm2_data_i);
    bus1.oc_data_i(oc_data_i);

    bus1.tm1_addr_o(tm1_addr_o);
    bus1.tm2_addr_o(tm2_addr_o);
    bus1.oc_addr_o(oc_addr_o);

    bus1.tm1_rd_o(tm1_rd_o);
    bus1.tm2_rd_o(tm2_rd_o);
    bus1.oc_rd_o(oc_rd_o);

    bus1.tm1_wr_o(tm1_wr_o);
    bus1.tm2_wr_o(tm2_wr_o);
    bus1.oc_wr_o(oc_wr_o);

    timer tm1("tm1");
    tm1.clk_i(clock);
    tm1.rst_i(rst);
    tm1.addr_i(tm1_addr_o);
    tm1.data_i(data_o);
    tm1.data_o(tm1_data_i);
    tm1.rd_i(tm1_rd_o);
    tm1.wr_i(tm1_wr_o);
    tm1.tval_o(tm1_val);
    tm1.tm_of(tm1_of);

    timer tm2("tm2");
    tm2.clk_i(clock);
    tm2.rst_i(rst);
    tm2.addr_i(tm2_addr_o);
    tm2.data_i(data_o);
    tm2.data_o(tm2_data_i);
    tm2.rd_i(tm2_rd_o);
    tm2.wr_i(tm2_wr_o);
    tm2.tval_o(tm2_val);
    tm2.tm_of(tm2_of);

    oc oc1("oc1");
    oc1.clk_i(clock);
    oc1.rst_i(rst);
    oc1.addr_i(oc_addr_o);
    oc1.data_i(data_o);
    oc1.data_o(oc_data_i);
    oc1.rd_i(oc_rd_o);
    oc1.wr_i(oc_wr_o);
    oc1.tms[0](tm1_val);
    oc1.tms_overflow[0](tm1_of);
    oc1.tms[1](tm2_val);
    oc1.tms_overflow[1](tm2_of);
    oc1.outs(outs);

    sc_trace_file *wf = sc_create_vcd_trace_file("wave_cpu");
    sc_trace(wf, obj.clk_i, "cpu_clk");
    sc_trace(wf, obj.rd_o, "cpu_rd_o");
    sc_trace(wf, obj.wr_o, "cpu_wr_o");
    sc_trace(wf, obj.addr_o, "cpu_addr_o");
    sc_trace(wf, obj.data_o, "cpu_data_o");
    sc_trace(wf, obj.data_i, "cpu_data_i");

    sc_trace(wf, oc1.outs, "oc_outs");
    sc_trace(wf, oc1.tms[0], "oc_tms_1");
    sc_trace(wf, oc1.tms_overflow[0], "oc_tm1_of");
    sc_trace(wf, oc1.addr_i, "oc_addr_o");
    sc_trace(wf, oc1.data_i, "oc_data_o");
    sc_trace(wf, oc1.data_o, "oc_oc_data_i");
    sc_trace(wf, oc1.rd_i, "oc_oc_rd_o");
    sc_trace(wf, oc1.wr_i, "oc_oc_wr_o");
    sc_trace(wf, oc1.tms[1], "oc_tm2_val");
    sc_trace(wf, oc1.tms_overflow[1], "oc_tm2_of");

    sc_trace(wf, bus1.addr_i, "bus_addr_i");
    sc_trace(wf, bus1.rd_i, "bus_rd_i");
    sc_trace(wf, bus1.wr_i, "bus_wr_i");
    sc_trace(wf, bus1.data_o, "bus_data_o");
    sc_trace(wf, bus1.tm1_data_i, "bus_tm1_data_i");
    sc_trace(wf, bus1.tm2_data_i, "bus_tm2_data_i");
    sc_trace(wf, bus1.oc_data_i, "bus_oc_data_i");
    sc_trace(wf, bus1.tm1_addr_o, "bus_tm1_addr_o");
    sc_trace(wf, bus1.tm2_addr_o, "bus_tm2_addr_o");
    sc_trace(wf, bus1.oc_addr_o, "bus_oc_addr_o");
    sc_trace(wf, bus1.tm1_rd_o, "bus_tm1_rd_o");
    sc_trace(wf, bus1.tm2_rd_o, "bus_tm2_rd_o");
    sc_trace(wf, bus1.oc_rd_o, "bus_oc_rd_o");
    sc_trace(wf, bus1.tm1_wr_o, "bus_tm1_wr_o");
    sc_trace(wf, bus1.tm2_wr_o, "bus_tm2_wr_o");
    sc_trace(wf, bus1.oc_wr_o, "bus_oc_wr_o");

    sc_trace(wf, tm1.addr_i, "tm1_addr_i");
    sc_trace(wf, tm1.data_i, "tm1_data_i");
    sc_trace(wf, tm1.data_o, "tm1_data_o");
    sc_trace(wf, tm1.rd_i, "tm1_rd_o");
    sc_trace(wf, tm1.wr_i, "tm1_wr_o");
    sc_trace(wf, tm1.tval_o, "tm1_val");
    sc_trace(wf, tm1.tm_of, "tm1_of");
    sc_trace(wf, tm2.addr_i, "tm2_addr_i");
    sc_trace(wf, tm2.data_i, "tm2_data_i");
    sc_trace(wf, tm2.data_o, "tm2_data_o");
    sc_trace(wf, tm2.rd_i, "tm2_rd_o");
    sc_trace(wf, tm2.wr_i, "tm2_wr_o");
    sc_trace(wf, tm2.tval_o, "tm2_val");
    sc_trace(wf, tm2.tm_of, "tm2_of");
    sc_start();

    return 0;
}
