vlib work
vlib activehdl

vlib activehdl/xil_defaultlib
vlib activehdl/xpm
vlib activehdl/microblaze_v10_0_4
vlib activehdl/lib_cdc_v1_0_2
vlib activehdl/proc_sys_reset_v5_0_12
vlib activehdl/axi_lite_ipif_v3_0_4
vlib activehdl/lib_pkg_v1_0_2
vlib activehdl/axi_timer_v2_0_16
vlib activehdl/interrupt_control_v3_1_4
vlib activehdl/axi_gpio_v2_0_16
vlib activehdl/generic_baseblocks_v2_1_0
vlib activehdl/axi_infrastructure_v1_1_0
vlib activehdl/axi_register_slice_v2_1_14
vlib activehdl/fifo_generator_v13_2_0
vlib activehdl/axi_data_fifo_v2_1_13
vlib activehdl/axi_crossbar_v2_1_15
vlib activehdl/lmb_v10_v3_0_9
vlib activehdl/lmb_bram_if_cntlr_v4_0_13
vlib activehdl/blk_mem_gen_v8_4_0
vlib activehdl/lib_srl_fifo_v1_0_2
vlib activehdl/axi_uartlite_v2_0_18
vlib activehdl/blk_mem_gen_v8_3_6
vlib activehdl/axi_bram_ctrl_v4_0_12
vlib activehdl/axi_protocol_converter_v2_1_14

vmap xil_defaultlib activehdl/xil_defaultlib
vmap xpm activehdl/xpm
vmap microblaze_v10_0_4 activehdl/microblaze_v10_0_4
vmap lib_cdc_v1_0_2 activehdl/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_12 activehdl/proc_sys_reset_v5_0_12
vmap axi_lite_ipif_v3_0_4 activehdl/axi_lite_ipif_v3_0_4
vmap lib_pkg_v1_0_2 activehdl/lib_pkg_v1_0_2
vmap axi_timer_v2_0_16 activehdl/axi_timer_v2_0_16
vmap interrupt_control_v3_1_4 activehdl/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_16 activehdl/axi_gpio_v2_0_16
vmap generic_baseblocks_v2_1_0 activehdl/generic_baseblocks_v2_1_0
vmap axi_infrastructure_v1_1_0 activehdl/axi_infrastructure_v1_1_0
vmap axi_register_slice_v2_1_14 activehdl/axi_register_slice_v2_1_14
vmap fifo_generator_v13_2_0 activehdl/fifo_generator_v13_2_0
vmap axi_data_fifo_v2_1_13 activehdl/axi_data_fifo_v2_1_13
vmap axi_crossbar_v2_1_15 activehdl/axi_crossbar_v2_1_15
vmap lmb_v10_v3_0_9 activehdl/lmb_v10_v3_0_9
vmap lmb_bram_if_cntlr_v4_0_13 activehdl/lmb_bram_if_cntlr_v4_0_13
vmap blk_mem_gen_v8_4_0 activehdl/blk_mem_gen_v8_4_0
vmap lib_srl_fifo_v1_0_2 activehdl/lib_srl_fifo_v1_0_2
vmap axi_uartlite_v2_0_18 activehdl/axi_uartlite_v2_0_18
vmap blk_mem_gen_v8_3_6 activehdl/blk_mem_gen_v8_3_6
vmap axi_bram_ctrl_v4_0_12 activehdl/axi_bram_ctrl_v4_0_12
vmap axi_protocol_converter_v2_1_14 activehdl/axi_protocol_converter_v2_1_14

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"/home/maar/.local/vivado/Vivado/2017.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/home/maar/.local/vivado/Vivado/2017.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"/home/maar/.local/vivado/Vivado/2017.3/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work microblaze_v10_0_4 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5eb2/hdl/microblaze_v10_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_microblaze_0_0/sim/uc_system_microblaze_0_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../bd/uc_system/ip/uc_system_clk_wiz_0_0/uc_system_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/uc_system/ip/uc_system_clk_wiz_0_0/uc_system_clk_wiz_0_0.v" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_12 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/f86a/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_proc_sys_reset_0_0/sim/uc_system_proc_sys_reset_0_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/cced/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_pkg_v1_0_2 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vcom -work axi_timer_v2_0_16 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/f3cd/hdl/axi_timer_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_axi_timer_0_0/sim/uc_system_axi_timer_0_0.vhd" \

vcom -work interrupt_control_v3_1_4 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/8e66/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_16 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/e9c1/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_axi_gpio_0_0/sim/uc_system_axi_gpio_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_14  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/a259/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_0  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/0798/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_0 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/0798/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_0  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/0798/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_13  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/74ae/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_15  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/a1b8/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../bd/uc_system/ip/uc_system_xbar_1/sim/uc_system_xbar_1.v" \

vcom -work lmb_v10_v3_0_9 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/78eb/hdl/lmb_v10_v3_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_dlmb_v10_0/sim/uc_system_dlmb_v10_0.vhd" \
"../../../bd/uc_system/ip/uc_system_ilmb_v10_0/sim/uc_system_ilmb_v10_0.vhd" \

vcom -work lmb_bram_if_cntlr_v4_0_13 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/0739/hdl/lmb_bram_if_cntlr_v4_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_dlmb_bram_if_cntlr_0/sim/uc_system_dlmb_bram_if_cntlr_0.vhd" \
"../../../bd/uc_system/ip/uc_system_ilmb_bram_if_cntlr_0/sim/uc_system_ilmb_bram_if_cntlr_0.vhd" \

vlog -work blk_mem_gen_v8_4_0  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/e50b/simulation/blk_mem_gen_v8_4.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../bd/uc_system/ip/uc_system_lmb_bram_0/sim/uc_system_lmb_bram_0.v" \
"../../../bd/uc_system/sim/uc_system.v" \
"../../../bd/uc_system/ip/uc_system_bram_interconnect_0_0/sim/uc_system_bram_interconnect_0_0.v" \

vcom -work lib_srl_fifo_v1_0_2 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_uartlite_v2_0_18 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/a8a5/hdl/axi_uartlite_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_axi_uartlite_0_0/sim/uc_system_axi_uartlite_0_0.vhd" \

vlog -work blk_mem_gen_v8_3_6  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/2751/simulation/blk_mem_gen_v8_3.v" \

vcom -work axi_bram_ctrl_v4_0_12 -93 \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ffa3/hdl/axi_bram_ctrl_v4_0_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/uc_system/ip/uc_system_axi_bram_ctrl_0_0/sim/uc_system_axi_bram_ctrl_0_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../bd/uc_system/ip/uc_system_output_compare_0_1/sim/uc_system_output_compare_0_1.v" \
"../../../bd/uc_system/ip/uc_system_timer_1_2/sim/uc_system_timer_1_2.v" \
"../../../bd/uc_system/ip/uc_system_timer_0_2/sim/uc_system_timer_0_2.v" \

vlog -work axi_protocol_converter_v2_1_14  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/33cc/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/5123" "+incdir+../../../../microbblaze.srcs/sources_1/bd/uc_system/ipshared/ec67/hdl" \
"../../../bd/uc_system/ip/uc_system_auto_pc_0/sim/uc_system_auto_pc_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

