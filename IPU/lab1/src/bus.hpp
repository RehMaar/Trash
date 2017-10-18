#ifndef bus_hpp_INCLUDED
#define bus_hpp_INCLUDED

#include <systemc.h>
#include "defines.hpp"
#include "timer.hpp"
#include "output_compare.hpp"
#include "mem_map.hpp"


SC_MODULE (bus) {
    sc_in_clk          clk_i;
    sc_in<bool>        rst_i;

    /* From Master. */
    sc_in<uint32_t> addr_i;
    sc_in<bool>     rd_i;
    sc_in<bool>     wr_i;
    /* To Master */
    sc_out<uint32_t> data_o;

    /* To slaves. */
    /* Timer 1. */
    sc_in<uint32_t>  tm1_data_i; /* From slave. */
    sc_out<uint32_t> tm1_addr_o; /* To slave.   */
    sc_out<bool>     tm1_rd_o;
    sc_out<bool>     tm1_wr_o;
    /* Timer 2. */
    sc_in<uint32_t>  tm2_data_i;
    sc_out<uint32_t> tm2_addr_o;
    sc_out<bool>     tm2_rd_o;
    sc_out<bool>     tm2_wr_o;

    /* Output Compare. */
    sc_in<uint32_t>  oc_data_i;
    sc_out<uint32_t> oc_addr_o;
    sc_out<bool>     oc_rd_o;
    sc_out<bool>     oc_wr_o;

    struct slave_signals {
        sc_in <uint32_t> *data_i;
        sc_out<uint32_t> *addr_o;
        sc_out<bool>     *rd_o;
        sc_out<bool>     *wr_o;
    };

    enum slave_addr {
        TM1,
        TM2,
        OC,
        SLAVE_NUM
    };

    slave_signals channels[SLAVE_NUM] = {
        { &tm1_data_i, &tm1_addr_o, &tm1_rd_o, &tm1_wr_o},
        { &tm2_data_i, &tm2_addr_o, &tm2_rd_o, &tm2_wr_o},
        { &oc_data_i, &oc_addr_o, &oc_rd_o, &oc_wr_o}
    };

    std::pair<addr_t, slave_addr> decode(mem_map addr);

    void channel_switch();

public:
    SC_CTOR(bus);
};

#endif // bus_hpp_INCLUDED
