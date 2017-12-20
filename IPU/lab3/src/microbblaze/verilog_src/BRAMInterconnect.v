module bram_interconnect(
    input clk_i,
    input rst_i,

    /* BRAM signals */
    input        en_i,      /* Enable Signal.       */
    input [3:0]  we_bi,     /* Write Enable Signal. */
    input [12:0] addr_bi,   /* Address Bus.         */
    input [31:0] wrdata_bi, /* Write Data Bus.      */

    input [31:0] s1_rddata_bi, /* Read Data Bus. */
    input [31:0] s2_rddata_bi, /* Read Data Bus. */
    input [31:0] s3_rddata_bi, /* Read Data Bus. */

    output reg [31:0] rddata_bo,

    output reg [12:0] s1_addr_bo,
    output reg [31:0] s1_wrdata_bo,
    output reg [3:0]  s1_we_bo,
    output reg        s1_en_o,

    output reg [12:0] s2_addr_bo,
    output reg [31:0] s2_wrdata_bo,
    output reg [3:0]  s2_we_bo,
    output reg        s2_en_o,

    output reg [12:0] s3_addr_bo,
    output reg [31:0] s3_wrdata_bo,
    output reg [3:0]  s3_we_bo,
    output reg        s3_en_o
);

	reg en_prev;
	reg [12:0] addr_prev;

    //always @(we_bi or en_i or wrdata_bi or addr_bi )
    always @(posedge clk_i)
    begin
        if (en_i && we_bi)
        begin
            case (addr_bi)
            	/* To Timer 1. */
                'h0, 'h4, 'h8 :
                begin
                    s2_addr_bo   <= (addr_bi);
                    s2_wrdata_bo <= (wrdata_bi);
                    s2_en_o      <= (en_i);
                    s2_we_bo     <= (we_bi);
                end
				/* To Timer 2. */
                'h0C, 'h10, 'h14 :
                begin
                    s3_addr_bo   <= (addr_bi -'h0C);
                    s3_wrdata_bo <= (wrdata_bi);
                    s3_en_o      <= (en_i);
                    s3_we_bo     <= (we_bi);
                end
				/* To OC.*/
                'h18, 'h1C :
                begin
                    s1_addr_bo   <= (addr_bi -'h18);
                    s1_wrdata_bo <= (wrdata_bi);
                    s1_en_o      <= (en_i);
                    s1_we_bo     <= (we_bi);
                end
            endcase
        end
        else if (en_i && !en_prev)
        begin
            case (addr_bi)
                'h0, 'h4, 'h8:
                begin
                    s2_addr_bo <= (addr_bi);
                    s2_en_o    <= en_i;
                end

                'h0C, 'h10, 'h14:
                begin
                    s3_addr_bo <= (addr_bi -'h0C);
                    s3_en_o    <= en_i;
                end

                'h18, 'h1C:
                begin
                    s1_addr_bo <= (addr_bi -'h18);
                	s1_en_o    <= en_i;
                end
            endcase
            en_prev   <= en_i;
            addr_prev <= addr_bi;
        end
        else if (en_prev)
        begin
			en_prev <= 0;
            case (addr_prev)
                'h0, 'h4, 'h8:
                begin
                    s2_en_o   <= 0;
                    rddata_bo <= s2_rddata_bi;
                end
                'h0C, 'h10, 'h14:
                begin
                    s3_en_o   <= 0;
                    rddata_bo <= s3_rddata_bi;
                end
                'h18, 'h1C:
                begin
                	s1_en_o   <= 0;
                	rddata_bo <= s1_rddata_bi;
               	end
            endcase
        end
        else 
        begin
        	en_prev      <= 0;
        	addr_prev    <= 0;
        	//rddata_bo    <= 0;
            s1_addr_bo   <= 0;
            s1_wrdata_bo <= 0;
            s1_en_o      <= 0;
            s1_we_bo     <= 0;
            s2_addr_bo   <= 0;
            s2_wrdata_bo <= 0;
            s2_en_o      <= 0;
            s2_we_bo     <= 0;
            s3_addr_bo   <= 0;
            s3_wrdata_bo <= 0;
            s3_en_o      <= 0;
            s3_we_bo     <= 0;
        end
    end
endmodule
