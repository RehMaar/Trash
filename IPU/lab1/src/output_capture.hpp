#ifndef output_capture_hpp_INCLUDED
#define output_capture_hpp_INCLUDED

SC_MODULE (output_capture) {

	sc_in_clk	clk_i;
    sc_in<bool> rst_i;

    /* Bus interface. */
    sc_in<uint32_t>  addr_i;
    sc_in<uint32_t>  data_i;
    sc_in<bool>      rd_i;
    sc_in<bool>      wr_i;

    sc_out<uint32_t> data_o;

	/* Timers. */
	sc_in<uint32_t>  timer1;
	sc_in<uint32_t>  timer2;

	/* Output signal. */
	sc_out<bool> outs;

	uint32_t occonf;
	uint32_t ocr;

#define READ_BIT(buf_, bit_) ((buf_ >> bit_) & 1)

#define TOGGLE_BIT(buf_, bit_, val_)\
		(but_ ^ (((but_ >> bit_) ^ val_) << bit_))

	enum oc_mode {
		SIGNAL_OFF = 0x0,
		SIGNAL_TO_ONE,
		SIGNAL_TO_ZERO,
		SIGNAL_TOGGLE,
		SIGNAL_PWM_TO_ONE,
		SIGNAL_PWM_TO_ZERO
	};

	enum oc_timer {
		TIMER1 = 0x0,
		TIMER2
	};
 public:
    void reset();
    void read();
    void write();

    SC_CTOR (output_capture) {
        SC_METHOD (reset);
            sensitive << rst_i;
        SC_METHOD (read);
            sensitive << clk_i.pos();
        SC_METHOD (write);
            sensitive << clk_i.pos();
    }

};

#endif // output_capture_hpp_INCLUDED
