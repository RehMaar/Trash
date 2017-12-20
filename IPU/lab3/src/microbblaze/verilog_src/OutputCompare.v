module output_compare (
    input        clk_i,
    input        rst_i,

    input [12:0] addr_i,
    input [31:0] data_i,
    input        en_i,
    input [3:0]	 we_i,

    input [31:0] tm1,
    input        tm1_of,
    input [31:0] tm2,
    input        tm2_of,
    
    output reg [31:0]   data_o,

    output reg outs
);

    /* Timers */
    localparam OC_TM1 = 0;
    localparam OC_TM2 = 1;

    /* OC conf*/
    localparam OC_MODE_START = 0;
    localparam OC_MODE_END   = 2;
    localparam OC_TM_WRK     = 3;

    /* OC modes. */
    localparam OC_OFF            = 'h0;
    localparam OC_SIMPLE_TO_ONE  = 'h1;
    localparam OC_SIMPLE_TO_ZERO = 'h2;
    localparam OC_TOGGLE         = 'h3;
    localparam PWM_TO_ONE        = 'h4;
    localparam PWM_TO_ZERO       = 'h5;

    /* Register addresses. */
    localparam OCCONF_ADDR     = 'h0;
    localparam OCR_ADDR 	   = 'h4;

    reg [31:0] occonf;
    reg [31:0] ocr;

    always @(posedge rst_i or posedge clk_i)
    begin
    	if (rst_i)
    	begin
			occonf <= 0;
			ocr    <= 0;
			data_o <= 0;
    	end
        else if (en_i && we_i)
        begin
        	case (addr_i)
                OCCONF_ADDR: occonf <= data_i;
                OCR_ADDR:    ocr    <= data_i;
            endcase
        end
    	else if (en_i)
    	begin
        	case (addr_i)
                OCCONF_ADDR: data_o <= occonf;
                OCR_ADDR:    data_o <= ocr;
            endcase
        end
    end

    wire eq = (occonf[OC_TM_WRK] == OC_TM1 ? tm1 : tm2) == ocr;
    wire of = occonf[OC_TM_WRK] == OC_TM1 ? tm1_of : tm2_of;

    /* Out logic. */
    always @*
    begin
        case (occonf[OC_MODE_END:OC_MODE_START])
        	OC_OFF:			   outs = 0;
            OC_SIMPLE_TO_ONE:  outs = 0 ^ eq;
            OC_SIMPLE_TO_ZERO: outs = 1 ^ eq;
            OC_TOGGLE:         outs = ~outs;
            PWM_TO_ONE:
            begin
            	if (eq && ~of)
                    outs = 1;
                else if (of)
                	outs = 0;
            end
            PWM_TO_ZERO:
            begin
            	if (eq && ~of)
                    outs = 0;
                else if (of)
                	outs = 1;
            end
        endcase
    end

endmodule
