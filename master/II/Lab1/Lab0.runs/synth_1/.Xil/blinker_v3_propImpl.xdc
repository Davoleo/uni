set_property SRC_FILE_INFO {cfile:C:/Dev/uni/master/II/Lab0/Lab0.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc rfile:../../../Lab0.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc id:1} [current_design]
set_property src_info {type:XDC file:1 line:9 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN M9    IOSTANDARD LVCMOS33 } [get_ports { clk }]; #IO_L13P_T2_MRCC_14 Sch=gclk
set_property src_info {type:XDC file:1 line:10 export:INPUT save:INPUT read:READ} [current_design]
create_clock -add -name sys_clk_pin -period 83.33 -waveform {0 41.66} [get_ports { clk }];
set_property src_info {type:XDC file:1 line:13 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN D2    IOSTANDARD LVCMOS33 } [get_ports { btn[0] }]; #IO_L6P_T0_34 Sch=btn[0]
set_property src_info {type:XDC file:1 line:14 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN D1    IOSTANDARD LVCMOS33 } [get_ports { btn[1] }]; #IO_L6N_T0_VREF_34 Sch=btn[1]
set_property src_info {type:XDC file:1 line:17 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN F1    IOSTANDARD LVCMOS33 } [get_ports { led0_b }]; #IO_L10N_T1_34 Sch=led0_b
set_property src_info {type:XDC file:1 line:18 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN D3    IOSTANDARD LVCMOS33 } [get_ports { led0_g }]; #IO_L9N_T1_DQS_34 Sch=led0_g
set_property src_info {type:XDC file:1 line:19 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN F2    IOSTANDARD LVCMOS33 } [get_ports { led0_r }]; #IO_L10P_T1_34 Sch=led0_r
set_property src_info {type:XDC file:1 line:22 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN E2    IOSTANDARD LVCMOS33 } [get_ports { led[0] }]; #IO_L8P_T1_34 Sch=led[1]
set_property src_info {type:XDC file:1 line:23 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN K1    IOSTANDARD LVCMOS33 } [get_ports { led[1] }]; #IO_L16P_T2_34 Sch=led[2]
set_property src_info {type:XDC file:1 line:24 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN J1    IOSTANDARD LVCMOS33 } [get_ports { led[2] }]; #IO_L16N_T2_34 Sch=led[3]
set_property src_info {type:XDC file:1 line:25 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN E1    IOSTANDARD LVCMOS33 } [get_ports { led[3] }]; #IO_L8N_T1_34 Sch=led[4]
