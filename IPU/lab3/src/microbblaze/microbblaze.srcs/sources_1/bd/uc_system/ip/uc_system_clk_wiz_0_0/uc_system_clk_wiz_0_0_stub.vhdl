-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.3 (lin64) Build 2018833 Wed Oct  4 19:58:07 MDT 2017
-- Date        : Sun Nov 12 12:19:05 2017
-- Host        : origin running 64-bit unknown
-- Command     : write_vhdl -force -mode synth_stub
--               /home/maar/stdy/4c/SVViPU/lab2/microbblaze/microbblaze.srcs/sources_1/bd/uc_system/ip/uc_system_clk_wiz_0_0/uc_system_clk_wiz_0_0_stub.vhdl
-- Design      : uc_system_clk_wiz_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity uc_system_clk_wiz_0_0 is
  Port ( 
    clk_out1 : out STD_LOGIC;
    reset : in STD_LOGIC;
    locked : out STD_LOGIC;
    clk_in1 : in STD_LOGIC
  );

end uc_system_clk_wiz_0_0;

architecture stub of uc_system_clk_wiz_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk_out1,reset,locked,clk_in1";
begin
end;
