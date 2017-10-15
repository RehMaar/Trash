#ifndef output_capture_hpp_INCLUDED
#define output_capture_hpp_INCLUDED

SC_MODULE (output_compare) {

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
        OCR_ADDR
        REG_NUM
    };

    SC_CTOR (output_compare);

private:

    /* OC registers. */
    sc_uint<32> occonf;
    sc_uint<32> ocr;

	/* Bits ranges. */
    enum oc_conf {
        OC_MODE_START = 0,
        OC_MODE_END   = 2,
        TM_WRK     	  = 3;
    };

    /* OC modes. */
    enum oc_mode {
        OFF = 0x0,
        TO_ONE,
        TO_ZERO,
        TOGGLE,
        PWM_TO_ONE,
        PWM_TO_ZERO
    };

    /* Timers' addreses in the module. */
    enum oc_timer {
        TIMER1 = 0x0,
        TIMER2
    };
	


    sc_uint<32> reg_map[REG_NUM] = {
        &occonf,
        &ocr
    };
	/* Base operations. */
    void reset(); 
    void read();
    void write();

	bool cmp_ocr();
	void out_logic();

    sc_uint<32> *oc::get_register(uint32_t addr);
};

#endif // output_capture_hpp_INCLUDED
