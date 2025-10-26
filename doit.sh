#!/bin/sh
# Shebang line: tells system to use /bin/sh shell interpreter
# This makes the file executable as a shell script

# CLEANUP PHASE - Remove old build artifacts
rm -rf obj_dir 
# rm = remove command
# -r = recursive (remove directories and all contents)
# -f = force (don't prompt for confirmation, ignore errors if files don't exist)
# obj_dir = directory containing previous Verilator build files
# Purpose: Start with clean build environment

rm -f counter.vcd
# rm = remove command  
# -f = force (don't prompt, ignore if file doesn't exist)
# counter.vcd = previous waveform file
# Purpose: Remove old waveform to start fresh

# VERILATOR TRANSLATION PHASE - Convert SystemVerilog to C++
verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp
# verilator = Verilator simulator command
# -Wall = Enable ALL warnings (Warnings All)
#        Shows potential issues in Verilog code
# --cc = Generate C++ code (C++ Compilation)
#        Creates C++ wrapper for Verilog module
# --trace = Enable waveform tracing capability
#          Generates code to create VCD files for GTKWave
# counter.sv = Input SystemVerilog source file
# --exe counter_tb.cpp = Link with C++ testbench executable
#                        Creates executable that includes testbench

# BUILD PHASE - Compile generated C++ code
make -j -C obj_dir/ -f Vcounter.mk Vcounter
# make = GNU Make build tool
# -j = Use parallel jobs (multiple CPU cores)
#      Speeds up compilation by using all available cores
# -C obj_dir/ = Change directory to obj_dir/ before running make
#               All make operations happen in obj_dir/
# -f Vcounter.mk = Use Vcounter.mk as the Makefile
#                   Verilator generates this custom Makefile
# Vcounter = Target to build (the executable)
#            This is the final simulation executable

# SIMULATION PHASE - Run the compiled simulation
obj_dir/Vcounter
# obj_dir/Vcounter = Path to the compiled executable
#                    This runs the simulation and generates counter.vcd
#                    The simulation will run for 300 cycles as defined in testbench