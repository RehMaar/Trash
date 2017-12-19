`timescale 1ns / 1ps

/*
(bram_en,
    bram_we,
    capturing,
    clk_mb,
    generateout0,
    gpios_tri_o,
    outs,
    pwm0,
    reset_mb,
    timer_interrupt,
    uart_rtl_0_rxd,
    uart_rtl_0_txd);*/

module sim_tb;

    reg clk;
    reg rst;
    reg capturetrig0;
    wire [15:0] gpios;
    //wire timer_inturrupt;
	wire outs;
	reg rxd;
	wire txd;

    uc_system_wrapper uc(
        .clk_mb(clk),
        .reset_mb(rst),
    
        .capturetrig(outs),

        .gpio_rtl_0_tri_o(gpios),

        .outs(outs),
        .uart_rtl_0_rxd(rxd),
        .uart_rtl_0_txd(txd)
    );

    initial begin
        rst = 1;
        clk = 0;
        rxd = 1;
        //capturetrig0 = 0;
        #100;
        rst = 0;
        //capturetrig0 = outs;
    end
    
    always #5 clk = ~clk;
endmodule
