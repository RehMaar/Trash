//Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2017.3 (lin64) Build 2018833 Wed Oct  4 19:58:07 MDT 2017
//Date        : Mon Dec 18 18:46:15 2017
//Host        : origin running 64-bit unknown
//Command     : generate_target uc_system_wrapper.bd
//Design      : uc_system_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module uc_system_wrapper
   (capturetrig,
    clk_mb,
    gpio_rtl_0_tri_o,
    outs,
    reset_mb,
    uart_rtl_0_rxd,
    uart_rtl_0_txd);
  input capturetrig;
  input clk_mb;
  output [15:0]gpio_rtl_0_tri_o;
  output outs;
  input reset_mb;
  input uart_rtl_0_rxd;
  output uart_rtl_0_txd;

  wire capturetrig;
  wire clk_mb;
  wire [15:0]gpio_rtl_0_tri_o;
  wire outs;
  wire reset_mb;
  wire uart_rtl_0_rxd;
  wire uart_rtl_0_txd;

  uc_system uc_system_i
       (.capturetrig(capturetrig),
        .clk_mb(clk_mb),
        .gpio_rtl_0_tri_o(gpio_rtl_0_tri_o),
        .outs(outs),
        .reset_mb(reset_mb),
        .uart_rtl_0_rxd(uart_rtl_0_rxd),
        .uart_rtl_0_txd(uart_rtl_0_txd));
endmodule
