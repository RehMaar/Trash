#include <xil_io.h>

/* BRAM and submodules addresses. */
#define BRAM_ADDR               0xC0000000
/* Timer 1 addresses. */
#define TIMER1_TMR_ADDR         (BRAM_ADDR + 0x0)
#define TIMER1_TVAL_ADDR        (BRAM_ADDR + 0x4)
#define TIMER1_TCONF_ADDR       (BRAM_ADDR + 0x8)

/* Timer 2 addresses. */
#define TIMER2_TMR_ADDR         (BRAM_ADDR + 0x0 + 0xC)
#define TIMER2_TVAL_ADDR        (BRAM_ADDR + 0x4 + 0xC)
#define TIMER2_TCONF_ADDR       (BRAM_ADDR + 0x8 + 0xC)

/* Timer configuration. */
#define TCONF_TYPE_BIT	0
enum { INC, DEC };

#define TCONF_RUN_BIT		1
enum { STOP, RUN };

/* OC addresses. */
#define OC_OCCONF_ADDR          (BRAM_ADDR + 0x0 + 0x18)
#define OC_OCR_ADDR             (BRAM_ADDR + 0x4 + 0x18)

/* OC configuration. */
/* Bits from 0 to 2 is for mode. */
enum {
    OC_OFF = 0,
    OC_SIMPLE_TO_ONE,
    OC_SIMPLE_TO_ZERO,
    OC_TOGGLE,
    OC_PWM_TO_ONE,
    OC_PWM_TO_ZERO       
};

#define OC_TM_WRK		3
enum { OC_TM1, OC_TM2 };

/* AXI GPIO addresses. */
#define GPIO_ADDR       0x40000000

/* AXI Timer addresses. */
#define TIMER_ADDR      0x41C00000
#define TCSR0           (TIMER_ADDR)        /* Control/Status Register */
#define TLR0            (TIMER_ADDR + 0x4)  /* Timer load register */
#define TCR0            (TIMER_ADDR + 0x8)  /* Timer Counter Register */

#define TCSR1           (TIMER_ADDR + 0x10)     /* Control/Status Register */
#define TLR1            (TIMER_ADDR + 0x14)  /* Timer load register */
#define TCR1            (TIMER_ADDR + 0x18)  /* Timer Counter Register */

/* AXI TCSR0 bits. */
#define ENALL           10 /* Enable all timers. */
#define TINT            8 /* Timer 0 Interrupt. */
#define ENT             7 /* Enable timer 0. */
#define ENIT            6 /* Enable interrupts for timer 0. */
#define LOAD            5 /* Load timer 0. */
#define ARHT            4 /* Auto Reload / Hold Timer */
#define CAPT            3 /* Enable External Capture Trigger Timer (TODO: wtf?) */
#define UDT             1 /* Up/Down timer 0. */
#define MDT             0 /* Timer 0 mode: 0 -- generate, 1 -- capture. */

#define SET_BIT(_reg, _bit, _val) (_reg |= (_val << _bit)) /* TO FUCKING DO */
#define GET_BIT(_reg, _bit) ((_reg >> _bit) & 0x1)

typedef enum {
    INIT_HIGH,
    INIT_LOW,
    READ_ZERO,
    READ_ONE,
} state_t;

void
set_generate_module(unsigned int period)
{
    /* Set OC.  */
    unsigned int occonf = 0;
	SET_BIT(occonf, OC_TM_WRK, OC_TM1);
	occonf |= OC_PWM_TO_ZERO;

    Xil_Out32(OC_OCR_ADDR, period);
	Xil_Out32(OC_OCCONF_ADDR, occonf);


	/* Set Timers. */
	Xil_Out32(TIMER1_TMR_ADDR, period * 3);

	unsigned int tconf = 0;
	SET_BIT(tconf, TCONF_TYPE_BIT, DEC);
	SET_BIT(tconf, TCONF_RUN_BIT,  RUN);
	Xil_Out32(TIMER1_TCONF_ADDR, tconf);
}

int
main(void)
{
    set_generate_module(300);

    /* Set interrupt clear bit to reset interrupts.*/
    unsigned int tcsr = 0x0;

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
    SET_BIT(tcsr, TINT, 1);

    unsigned int val0 = 0, val1 = 0;
    unsigned int interval_zero;
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
                    interval_zero = (val0) - (val1);
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
                    Xil_Out32(GPIO_ADDR, ((val1) - (val0)));
                    state = READ_ZERO;
                }
            }
        }
    }

    return 0;
}
