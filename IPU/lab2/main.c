#include <xil_io.h>

/* AXI GPIO addresses. */
#define GPIO_ADDR       0x40000000

/* AXI Timer addresses. */
#define TIMER_ADDR      0x41C00000
#define TCSR0           (TIMER_ADDR)		/* Control/Status Register */
#define TLR0            (TIMER_ADDR + 0x4)  /* Timer load register */
#define TCR0            (TIMER_ADDR + 0x8)  /* Timer Counter Register */

#define TCSR1           (TIMER_ADDR + 0x10)		/* Control/Status Register */
#define TLR1            (TIMER_ADDR + 0x14)  /* Timer load register */
#define TCR1            (TIMER_ADDR + 0x18)  /* Timer Counter Register */

/* AXI TCSR0 bits. */
#define ENALL			10 /* Enable all timers. */
#define TINT			8 /* Timer 0 Interrupt. */
#define ENT			    7 /* Enable timer 0. */
#define ENIT			6 /* Enable interrupts for timer 0. */
#define LOAD			5 /* Load timer 0. */
#define ARHT			4 /* Auto Reload / Hold Timer */
#define CAPT			3 /* Enable External Capture Trigger Timer (TODO: wtf?) */
#define UDT			    1 /* Up/Down timer 0. */
#define MDT			    0 /* Timer 0 mode: 0 -- generate, 1 -- capture. */

#define SET_BIT(_reg, _bit, _val) (_reg |= (_val << _bit)) /* TO FUCKING DO */
#define GET_BIT(_reg, _bit) ((_reg >> _bit) & 0x1)

#define TIMING_INTERVAL(x) (((int)-1) - x + 2)


typedef enum {
	INIT_HIGH,
	INIT_LOW,
	READ_ZERO,
	READ_ONE,
} state_t;

/*
 * 1. Распознавать последовательность 011.
 * 2. Определять длительность каждого символа с помощью AXI Timer.
 * 3. Выводить длительность каждого символа на AXI GPIO
 * 4. После распознование последовательности вывести 0xFFFF на GPIO (до или после вывода длительности)
 */
int main(void) {

	unsigned int tcsr = 0x0;

	/* Load TLR value. */
	Xil_Out32(TCSR0, 0x20); /* 10 0000 */
	Xil_Out32(TCSR1, 0x20);
	/* Set load register to 0. */
	Xil_Out32(TLR0, 0);
	Xil_Out32(TLR1, 0);

	/* Set the same parameters for all timers. */
	SET_BIT(tcsr, CAPT, 1);
	SET_BIT(tcsr, ARHT, 1);
	SET_BIT(tcsr, ENIT, 1);
	SET_BIT(tcsr, MDT,  1);

	/* Set timers configuration. */
	Xil_Out32(TCSR1, tcsr);

	/* Enable all timers. */
	SET_BIT(tcsr, ENALL, 1);
	Xil_Out32(TCSR0, tcsr);

	/* Set interrupt clear bit to reset interrupts.*/
	SET_BIT(tcsr, TINT, 1);

	/* Timer 0 -- capture event -- to high.
	 * Timer 1 -- capture event -- to low.
	 */
	unsigned int val0 = 0, val1 = 0;
	unsigned int interval_zero; //, interval_one;
	state_t state = INIT_HIGH;
	while(1) {
		switch (state) {
			case INIT_HIGH: { /* Catch initial 1 (timer 0). */
				unsigned int tcsr0_cur = Xil_In32(TCSR0);
		    	if (GET_BIT(tcsr0_cur, TINT) == 1) {
		    		Xil_Out32(TCSR0, tcsr);
		    		state = INIT_LOW;
		    	}
				unsigned int tcsr1_cur = Xil_In32(TCSR1);
		    	if (GET_BIT(tcsr1_cur, TINT) == 1) {
		    		Xil_Out32(TCSR1, tcsr);
		    	}
				break;
			}
			case INIT_LOW: {
				unsigned int tcsr1_cur = Xil_In32(TCSR1);
		    	if (GET_BIT(tcsr1_cur, TINT) == 1) {
					val1 = Xil_In32(TLR1);
		    		Xil_Out32(TCSR1, tcsr);

		    		state = READ_ZERO;
		    	}
				break;
			}
			case READ_ZERO: { /* On T0INT save zero interval. */
				unsigned int tcsr0_cur = Xil_In32(TCSR0);
		    	if (GET_BIT(tcsr0_cur, TINT) == 1) {
		    		val0 = Xil_In32(TLR0);

		    		Xil_Out32(TCSR0, tcsr);

		    		interval_zero = val0 - val1;
		    		state = READ_ONE;
		    	}
				break;
			}
			case READ_ONE: { /* On T1INT save one interval */
				unsigned int tcsr1_cur = Xil_In32(TCSR1);
				if (GET_BIT(tcsr1_cur, TINT) == 1) {
					val1 = Xil_In32(TLR1);

					Xil_Out32(TCSR1, tcsr);

        			Xil_Out32(GPIO_ADDR, 0xffff);
        			Xil_Out32(GPIO_ADDR, (interval_zero));
        			Xil_Out32(GPIO_ADDR, (val1 - val0));
        			state = READ_ZERO;

				}
			}
		}
    }
    return 0;
}
