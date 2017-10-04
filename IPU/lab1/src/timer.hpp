#ifndef __SLAVE_TIMER_H__
#define __SLAVE_TIMER_H__

#include <stdint.h>
#include "systemc.h"

SC_MODULE (timer) {
    sc_in_clk       clk_i;
    sc_in<bool>     rst_i;
    /* Bus interface. */
    sc_in<uint32_t> addr_i;
    sc_in<uint32_t> data_i;
    sc_in<bool>     rd_i;
    sc_in<bool>     wr_i;

    sc_out<uint32_t> data_o;

public:
	enum reg_map_addr {
		TMR_ADDR = 0,
		TVAL_ADDR,
		TCONF_ADDR,
		REG_NUM
	};

    void reset();	/* Reset timer.   */
    void read(); 	/* Read from bus. */
    void write();	/* Write to bus.  */

    SC_CTOR (timer) {
        SC_METHOD (reset);
            sensitive << rst_i;
        SC_METHOD (count);
        	sensitive << clk_i.pos();
        SC_METHOD (read);
            sensitive << clk_i.pos();
        SC_METHOD (write);
            sensitive << clk_i.pos();
    }

private:

    sc_uint<32> tmr;
    sc_uint<32> tval;
    sc_uint<32> tconf;
/**
 * Bit 0: 0 -- inc, 1 -- dec.
 * Bit 1: 0 -- stop, 1 -- run.
 * 
 * Bit 2--31: reserved.
 */
enum {
    TYPE_BIT = 0x0,
        INC  = 0x0,
        DEC  = 0x1,
    RUN_BIT  = 0x1,
        STOP = 0x1,
        RUN  = 0x0,
};

	sc_uint<32> * reg_map[reg_map_addr::REG_NUM] = { 
    	&tmr,
    	&tval,
    	&tconf
	};

	sc_uint<32> *get_register(uint32_t addr);

    void count();

};

#endif  /* __SLAVE_TIMER_H__ */
