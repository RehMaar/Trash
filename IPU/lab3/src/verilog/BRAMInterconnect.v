module bram_interconnect(
	input clk_i,
	input rst_i,

	input en_i,
	input [3:0] we_bi,
	input [12:0] addr_bi,
	input [31:0] wrdata_bi,

	input [31:0] s1_rddata,
	input [31:0] s2_rddata,
	input [31:0] s3_rddata,

	output [31:0] rddata_o,

	output [12:0] s1_addr_bo,
	output [12:0] s1_wrdata_bo,
	output [3:0]  s1_we_bo,
	output		  s1_en_o,

	output [12:0] s2_addr_bo,
	output [12:0] s2_wrdata_bo,
	output [3:0]  s2_we_bo,
	output		  s2_en_o,

	output [12:0] s3_addr_bo,
	output [12:0] s3_wrdata_bo,
	output [3:0]  s3_we_bo,
	output		  s3_en_o
);


    always @(we_bi or en_i or wrdata_bi or addr_bi)
    begin
        if (en_i)
        begin
            case(addr_bi)
             'h0, 'h4, 'h8 :
             begin
                 s1_addr_bo    = (addr_bi ;
                 s1_wrdata_bo  = (wrdata_bi ;
                 s1_en_o       = (en_i ;
                 s1_we_bo      = (we_bi ;
             end

             'h0C, 'h10, 'h14 :
             begin
                 s2_addr_bo    = (addr_bi -'h0C ); /* TODO: check this. */
                 s2_wrdata_bo  = (wrdata_bi ;
                 s2_en_o       = (en_i ;
                 s2_we_bo      = (we_bi ;
             end

             'h18, 'h1C :
             begin
                 s3_addr_bo    = (addr_bi -'h18);
                 s3_wrdata_bo  = (wrdata_bi ;
                 s3_en_o       = (en_i ;
                 s3_we_bo      = (we_bi ;
             end
            endcase
        end
        else 
        begin
            s1_addr_bo    = (0);
            s1_wrdata_bo  = (0);
            s1_en_o       = (0);
            s1_we_bo      = (0);
            s2_addr_bo    = (0);
            s2_wrdata_bo  = (0);
            s2_en_o       = (0);
            s2_we_bo      = (0);
            s3_addr_bo    = (0);
            s3_wrdata_bo  = (0);
            s3_en_o       = (0);
            s3_we_bo      = (0);
        end
    end

    /* Read. */
    always @(s3_rddata_bi or s2_rddata_bi or s1_rddata_bi or en_o_reg)
    begin
        if (en_o_reg)
        begin
            case(addr_bi)
                'h0,  'h4,  'h8  : rddata_bo  = (s1_rddata_bi);
                'h0C, 'h10, 'h14 : rddata_bo  = (s2_rddata_bi);
                'h18, 'h1C       : rddata_bo  = (s3_rddata_bi);
            endcase
        end
        else 
            rddata_bo  = (0);
        end
    end

    always @(negedge clk_i)
        next_en_o_reg  <= (en_i &&!we_bi);

    always @(posedge clk_i or posedge rst_i)
    begin
        if (!rst_i &&clk_i)
            en_o_reg <= (next_en_o_reg ;
        else 
            en_o_reg <= (0);
    end
endmodule;
