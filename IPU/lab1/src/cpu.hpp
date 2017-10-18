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
	void write(mem_map addr, uint32_t val);
	uint32_t read(mem_map addr);

	SC_HAS_PROCESS(cpu);

	uint32_t w;

	enum fsm_state {
    	SET_OC,
		SET_TIMER,
		FIRST_SIGNAL,
		SECOND_SIGNAL,
		THIRD_SIGNAL
	};

public:
    cpu(sc_module_name nm, uint32_t w_ = 1) : sc_module(nm), w(w_) {
        SC_CTHREAD(generate_signal, clk_i.pos());
    }
};

#endif // cpu_hpp_INCLUDED

