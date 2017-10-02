#ifndef __SLAVE_TIMER_H__
#define __SLAVE_TIMER_H__

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

#define SET_MODE(tconf, mode)   (tconf[0] = mode)
#define IS_INC_MODE(tconf) 		(tconf[0] == INC)
#define SET_RUN (tconf, type)   (tconf[1] = type)
#define IS_RUN(tconf) 			(tconf[1] == RUN)
    enum {
        INC  = 0x0,
        DEC  = 0x1,
        RUN  = 0x0,
        STOP = 0x1,
    };
    sc_bv<32> tconf;

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
