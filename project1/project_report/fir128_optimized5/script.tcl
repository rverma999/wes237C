############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fir128_1_variable_bitwidth
set_top fir
add_files fir128_1_variable_bitwidth/fir.cpp
add_files fir128_1_variable_bitwidth/fir.h
add_files -tb fir128_1_variable_bitwidth/fir_test.cpp -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb fir128_1_variable_bitwidth/input.dat -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb fir128_1_variable_bitwidth/out.gold.dat -cflags "-Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu7ev-ffvf1517-3-e}
create_clock -period 10 -name default
source "./fir128_1_variable_bitwidth/solution1/directives.tcl"
csim_design -clean -profile -setup
csynth_design
cosim_design
export_design -format ip_catalog
