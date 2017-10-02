#ifndef __SLAVE_TIMER_H__
#define __SLAVE_TIMER_H__

#include <stdint.h>
#include "systemc.h"

SC_MODULE (timer) {
    sc_in_clk       clk_i;
    sc_in<bool>     rst_i;
    sc_in<uint32_t> addr_i;
    sc_in<uint32_t> data_i;
    sc_in<bool>     rd_i;
    sc_in<bool>     wr_i;

    sc_out<uint32_t> data_o;

    uint32_t tmr;
    uint32_t tval;

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

#define READ_BIT(buf_, bit_) ((buf_ >> bit_) & 1)

#define TOGGLE_BIT(buf_, bit_, val_)\
		(but_ ^ (((but_ >> bit_) ^ val_) << bit_))

#define SET_MODE(mode_, bit_) \
    (tconf = READ_BIT(tconf, bit_) == mode_ ?: TOGGLE_BIT(tconf, bit_, mode_))

    uint32_t tconf;

	enum {
		TMR_ADDR = 0,
		TVAL_ADDR,
		TCONF_ADDR,
		REG_NUM
	};

	uint32_t * reg_map[REG_NUM] = { 
    	&tmr,
    	&tval,
    	&tconf
	};

private:
	uint32_t *get_register(uint32_t addr);

public:

    void reset();
    void read();
    void write();
    void count();

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
};

#endif  /* __SLAVE_TIMER_H__ */
