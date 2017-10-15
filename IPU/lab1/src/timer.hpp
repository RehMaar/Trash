#ifndef __SLAVE_TIMER_H__
#define __SLAVE_TIMER_H__

#include <stdint.h>
#include "systemc.h"

SC_MODULE (timer) {
    sc_in_clk       clk_i;
    sc_in<bool>     rst_i;
    /* Bus interface. */
    sc_in<sc_uint<32>> addr_i;
    sc_in<sc_uint<32>> data_i;
    sc_in<bool>     rd_i;
    sc_in<bool>     wr_i;

    sc_out<sc_uint<32>> data_o;
    /* Timer interface. */
    sc_out<sc_uint<32>> tval_o;

    sc_uint<32> tmr;
    sc_uint<32> tval;
    sc_uint<32> tconf;

public:
	enum timer_reg_map {
		TMR_ADDR 	= 0x0,
		TVAL_ADDR,
		TCONF_ADDR,
		REG_NUM
	};

/**
 * Bit 0: 0 -- inc, 1 -- dec.
 * Bit 1: 0 -- stop, 1 -- run.
 * 
 * Bit 2--31: reserved.
 */
    enum timer_mode {
        TYPE_BIT = 0x0,
            INC  = 0x0,
            DEC  = 0x1,
        RUN_BIT  = 0x1,
            STOP = 0x0,
            RUN  = 0x1,
    };
    void reset();	/* Reset timer.   */
    void read(); 	/* Read from bus. */
    void write();	/* Write to bus.  */

    SC_CTOR (timer);

private:

	sc_uint<32> * reg_map[reg_map_addr::REG_NUM] = { 
    	&tmr,
    	&tval,
    	&tconf
	};

	sc_uint<32> *get_register(uint32_t addr);

    void count();
};

#endif  /* __SLAVE_TIMER_H__ */
