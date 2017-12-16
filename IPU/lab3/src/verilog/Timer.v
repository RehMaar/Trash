module timer(
	input clk_i,
	input rst_i,

	input addr_i,
	input data_i,
	input rd_i,
	input wr_i,

	output data_o,
	output tval_o,
	output tm_of
);

	reg [31:0] tmr;
	reg [31:0] tconf;
	reg [31:0] tval;

	assign tval_o = tval;

	enum {
		TMR_ADDR,
		TVAL_ADDR,
		TCONF_ADDR
	};

	enum {
		TYPE_BIT,
		RUN_BIT
	};
	enum { INC, DEC };
	enum { STOP, RUN };

	always @(posedge clk_i)
	begin
		if (rst_i)
		begin
    		tmr   = 0;
    		tconf = 0;
    		tval  = 0;
    	end
	end

	always @(posedge clk_i)
	begin
		if (rd_i)
		begin
			case (addr_i)
				TMR_ADDR:   data_o <= tmr;
    			TVAL_ADDR:  data_o <= tval;
        		TCONF_ADDR: data_o <= tconf;
            endcase
		end
	end

	always @(posedge clk_i)
	begin
		if (wr_i)
		begin
			case (addr_i)
				TMR_ADDR:   tmr   <= data_o;
    			TVAL_ADDR:  tval  <= data_o;
        		TCONF_ADDR: tconf <= data_o;
            endcase
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

endmodule;
