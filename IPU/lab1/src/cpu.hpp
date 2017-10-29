#ifndef cpu_hpp_INCLUDED
#define cpu_hpp_INCLUDED

#include <systemc.h>
#include "defines.hpp"
#include "mem_map.hpp"
#include "bus.hpp"

SC_MODULE(cpu) {
	sc_in_clk		clk_i;

	/* To slaves. */
	sc_out<bool> rd_o, wr_o;
	sc_out<uint32_t> addr_o, data_o;
	/* From slaves. */
	sc_in<uint32_t> data_i;

	void generate_signal();
    void generate_signal_simple();
    void generate_signal_long(uint32_t width);

	void write_reg(mem_map addr, uint32_t val);
	uint32_t read(mem_map addr);
	void set_oc(oc::oc_mode mode, oc::oc_timer tm);
    void set_timer(mem_map addr, timer::timer_mode m,
                   timer::timer_mode t);

	SC_HAS_PROCESS(cpu);

	uint32_t w;

public:
    cpu(sc_module_name nm, uint32_t w_ = 1) : sc_module(nm), w(w_) {
        SC_CTHREAD(generate_signal, clk_i.pos());
    }
};

#endif // cpu_hpp_INCLUDED

