#ifndef output_capture_hpp_INCLUDED
#define output_capture_hpp_INCLUDED

#include <systemc.h>

SC_MODULE (oc) {

    sc_in_clk   clk_i;
    sc_in<bool> rst_i;

    /* Bus interface. */
    sc_in<uint32_t>  addr_i;
    sc_in<uint32_t>  data_i;
    sc_in<bool>      rd_i;
    sc_in<bool>      wr_i;

    sc_out<uint32_t> data_o;

    /* Timers. */
    sc_in<uint32_t>  tms[2];
    sc_in<bool>		 tms_overflow[2];


    /* Output signal. */
    sc_out<bool> outs;

public:
    /* Register addresses in the module. */
    enum oc_reg_map {
        OCCONF_ADDR = 0x0,
        OCR_ADDR,
        REG_NUM
    };

    /* OC modes. */
    enum oc_mode {
        OFF = 0x0,
        SIMPLE_TO_ONE,
        SIMPLE_TO_ZERO,
        TOGGLE,
        PWM_TO_ONE,
        PWM_TO_ZERO
    };

	/* Bits ranges. */
    enum oc_conf {
        OC_MODE_START = 0,
        OC_MODE_END   = 2,
        TM_WRK     	  = 3
    };

    SC_CTOR (oc);

private:

    /* OC registers. */
    sc_uint<32> occonf;
    sc_uint<32> ocr;

	bool simple_mode;
	bool pwm_mode;
	bool toggle_mode;
	bool logic_rst;

    /* Timers' addreses in the module. */
    enum oc_timer {
        TIMER1 = 0x0,
        TIMER2
    };
	
    sc_uint<32> * reg_map[REG_NUM] = {
        &occonf,
        &ocr
    };
	/* Base operations. */
    void reset(); 
    void read();
    void write();


	bool cmp_ocr();
	void set_new_mode();
	void out_logic();

    sc_uint<32> *get_register(uint32_t addr);
};

#endif // output_capture_hpp_INCLUDED
