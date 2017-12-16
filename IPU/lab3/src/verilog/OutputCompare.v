module oc (
    input        clk,
    input        rst,

    input [31:0] addr_i,
    input [31:0] data_i,
    input        rd_i,
    input        wr_i,

    input [31:0] tm1,
    input        tm1_of,
    input [31:0] tm2,
    input        tm2_of,
    
    output       data_o,

    output       outs
);

    /* Timers */
    enum {
        OC_TM1 = 0,
        OC_TM2
    };

    /* OC conf*/
    enum {
        OC_MODE_START = 0,
        OC_MODE_END   = 2,
        OC_TM_WRK     = 3;
    };

    /* OC modes. */
    enum {
        OC_OFF = 0,
        OC_SIMPLE_TO_ONE,
        OC_SIMPLE_TO_ZERO,
        OC_TOGGLE,
        PWM_TO_ONE,
        PWM_TO_ZERO
    };

    /* Register addresses. */
    enum {
        OCCONF_ADDR,
        OCR_ADDR
    };

    reg [31:0] occonf;
    reg [31:0] ocr;

    reg reg_outs;
    assign outs = reg_outs;

    /* Reset registers. */
    always @(posedge rst)
    begin
        occonf    <= 0;
        ocr       <= 0;
        reg_outs  <= 0;
    end

    /* Read block. */
    always @(posedge clk)
    begin
        if (rd_i) {
            if (add_i == OCCONF_ADDR) {
                data_o = occonf;
            } else if (addr_i == OCR_ADDR) {
                data_o = ocr;
            }
        }
    end

    /* Write block. */
    always @(posedge clk)
    begin
        if (wr_i) {
            if (add_i == OCCONF_ADDR) {
                occonf = data_i;
            } else if (addr_i == OCR_ADDR) {
                ocr = data_i;
            }
        }
    end

    wire eq = occonf[OC_TM_WRK] == OC_TM1 ? tms1 : tms2;
    wire of = occonf[OC_TM_WRK] == OC_TM1 ? tms1_of : tms2_of;

    /* Out logic. */
    always @*
    begin
        case (occonf[OC_MODE_START:OC_MODE_END])
            OC_SIMPLE_TO_ONE:
                begin
                    reg_outs = 0 ^ eq;
                end
            OC_SIMPLE_TO_ZERO:
                begin
                    reg_outs = 1 ^ eq;
                end
            OC_TOGGLE:
                begin
                    reg_outs = ~reg_outs;
                end
            PWM_TO_ONE:
                begin
					reg_outs = eq && ~of;
                    //if (eq && ~of)
                    //    reg_outs = 1;
                    //else
                    //    reg_outs = 0;
                end
            PWM_TO_ZERO:
                begin
					reg_outs = ~(eq && ~of)
                    //if (eq && ~of)
                    //    reg_outs = 0;
                    //else
                    //    reg_outs = 1;
                end
        endcase
    end

endmodule;
