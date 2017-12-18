module timer(
	input clk_i,
	input rst_i,

	input [12:0] addr_i,
	input [31:0] data_i,
	input 		 en_i,
	input [3:0]  we_i,

	output reg [31:0] data_o,
	output     [31:0] tval_o,
	output reg tm_of
);

	reg [31:0] tmr;
	reg [31:0] tconf;
	reg [31:0] tval;

	assign tval_o = tval;

	localparam TMR_ADDR   = 'h0;
	localparam TVAL_ADDR  = 'h4;
	localparam TCONF_ADDR = 'h8;

	localparam TYPE_BIT = 0;
	localparam RUN_BIT  = 1;

	localparam INC = 0;
	localparam DEC = 1;

	localparam STOP = 0;
	localparam RUN  = 1;

	always @(negedge clk_i)
	begin
		if (rst_i)
		begin
    		tmr    <= 0;
    		tconf  <= 0;
    		tval   <= 0;
    		data_o <= 0;
    	end
		else if (en_i && we_i)
		begin
			case (addr_i)
				TMR_ADDR:   tmr   <= data_i;
    			TVAL_ADDR:  tval  <= data_i;
        		TCONF_ADDR: tconf <= data_i;
            endcase
		end
		else if (en_i)
		begin
			case (addr_i)
				TMR_ADDR:   data_o <= tmr;
    			TVAL_ADDR:  data_o <= tval;
        		TCONF_ADDR: data_o <= tconf;
            endcase
		end
		else begin
			data_o <= 'h0;
		end
	end

	always @(posedge clk_i)
	begin
		if (tconf[RUN_BIT] == RUN)
		begin
			if (tconf[TYPE_BIT] == INC)
			begin
    			tval  <= tval == tmr ? 0 : tval + 1;
    			tm_of <= tval == tmr;
    		end
    		else
			begin
				tval  <= tval == 0 ? tmr : tval - 1;
				tm_of <= tval == 0;
			end
		end
		else
			tm_of <= 0;
	end

endmodule
