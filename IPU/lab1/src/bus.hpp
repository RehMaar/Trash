#ifndef bus_hpp_INCLUDED
#define bus_hpp_INCLUDED

#include <systemc.h>
#include "defines.hpp"
#include "timer.hpp"


SC_METHOD (bus_matrix) {
    sc_in_clk          clk_i;
    sc_in<bool>        rst_i;

    /* From Master. */
    sc_in<sc_uint<32>> addr_i;
    sc_in<sc_uint<32>> data_i;
    sc_in<bool>        rd_i;
    sc_in<bool>        wr_i;
    /* To Master */
    sc_out<sc_uint<32>> data_o;

    /* To slaves. */
    /* Timer 1. */
    sc_out<sc_uint<32>> tm1_addr_o;
    sc_out<sc_uint<32>> tm1_data_o;
    sc_out<bool>        tm1_rd_o;
    sc_out<bool>        tm1_wr_o;
	/* Timer 2. */
    sc_in<sc_uint<32>> tm2_data_i;

    sc_out<sc_uint<32>> tm2_addr_o;
    sc_out<bool>        tm2_rd_o;
    sc_out<bool>        tm2_wr_o;

	/* Output Compare. */
    sc_in<sc_uint<32>> oc_data_i;

    sc_out<sc_uint<32>> oc_addr_o;
    sc_out<bool>        oc_rd_o;
    sc_out<bool>        oc_wr_o;

	struct slave_signals {
		sc_out<sc_uint<32>> data_i;
		sc_out<sc_uint<32>> addr_o;
		sc_out<bool> 	    rd_o;
		sc_out<bool>		wr_o;
	};

private:

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
	}

	slave_num decode(sc_uint<32> addr);

public:
	void swtich_channels();
};

#endif // bus_hpp_INCLUDED
