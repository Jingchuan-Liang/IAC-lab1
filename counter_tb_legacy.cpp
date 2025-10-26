// Header includes for Verilator simulation
#include "Vcounter.h"           // Generated Verilator header for the counter module
#include "verilated.h"          // Verilator's main header for simulation functionality
#include "verilated_vcd_c.h"    // Verilator's VCD tracing header for waveform generation

// Main function signature for Verilator testbench
int main(int argc, char **argv, char **env){
    // argc: Number of command line arguments passed to the program
    // argv: char **argv = pointer to pointer to char (array of strings)
    //      - First *: points to an array of char* (string pointers)
    //      - Second *: each char* points to a null-terminated string
    //      - Equivalent to: char *argv[] (array of string pointers)
    //      - Example: argv[0] = "./counter_tb", argv[1] = "--trace"
    // env: char **env = pointer to pointer to char (array of environment strings)
    //     - Same structure as argv but contains "KEY=VALUE" environment pairs
    //     - Example: env[0] = "PATH=/usr/bin", env[1] = "HOME=/home/user"
    // These parameters allow the testbench to receive Verilator-specific options
    // Variable declarations for simulation control
    int i;      // Outer loop counter: tracks simulation cycles (0 to 299)
                // Each iteration represents one complete clock cycle
                // Used to control when reset and enable signals change
    int clk;    // Inner loop counter: tracks clock edges within each cycle
                // Values: 0 (falling edge) and 1 (rising edge)
                // Creates complete clock waveform by toggling clk signal

    // Verilator initialization
    Verilated::commandArgs(argc,argv);  // Pass command line arguments to Verilator
    Vcounter* top = new Vcounter;       // Create instance of the counter module
    
    // Initialize trace dump for waveform generation
    Verilated::traceEverOn(true);       // Enable tracing for the simulation
    VerilatedVcdC* tfp = new VerilatedVcdC;  // Create VCD trace file object
    // tfp = "Trace File Pointer" - pointer to VCD (Value Change Dump) file object
    // VCD files store signal changes over time for waveform viewing in GTKWave
    top->trace(tfp,99);                 // Connect counter module to trace file with depth 99
    // Depth 99 = trace hierarchy depth (how many levels of module hierarchy to trace)
    // Higher depth = trace more nested modules, lower depth = trace only top-level signals
    // Depth 99 is very high, meaning trace ALL signals in the design
    tfp->open("counter.vcd");           // Open VCD file for writing waveform data

    // Initialize simulation inputs
    top->clk = 1;  // Set initial clock signal to high (1)
    top->rst = 1;  // Set reset signal to active (1)
    top->en = 0;   // Set enable signal to inactive (0)

    // MAIN SIMULATION LOOP - This is the heart of the testbench
    // Outer loop: Controls overall simulation timing and signal changes
    for (i=0; i<300; i++){              
        // i represents simulation cycle number (0 to 299)
        // Each iteration of this loop = 1 complete clock cycle
        
        // Inner loop: Creates the actual clock waveform (2 edges per cycle)
        for(clk=0; clk<2; clk++){       
            // clk=0: Falling edge of clock
            // clk=1: Rising edge of clock
            // This creates a complete clock cycle with both edges
            
            // Record current signal states to VCD file
            tfp->dump(2*i + clk);       
            // Time calculation: 2*i + clk creates unique timestamps
            // Example: i=0, clk=0 → time=0, i=0, clk=1 → time=1
// Update control signals AFTER each complete clock cycle
top->rst = (i<2) | (i==15);     
// Reset logic: rst = 1 when i<2 OR i==15
// PURPOSE: Test different scenarios to verify counter behavior
// i=0,1: Initial reset (rst=1) - Test: Does counter reset to 0?
// i=2-14: Normal operation (rst=0) - Test: Does counter work normally?
// i=15: Mid-simulation reset (rst=1) - Test: Does counter reset during operation?
// i=16-299: Normal operation (rst=0) - Test: Does counter continue after reset?            // Toggle the clock signal to create clock edges
            top->clk = !top->clk;       //注意这个clk 跟 这个for loop counter里的clk不是一个东西
            // First iteration: clk goes from 1→0 (falling edge)
            // Second iteration: clk goes from 0→1 (rising edge)
            
            // Evaluate the Verilog module with current signal values
            top->eval();                
            // This tells Verilator to process all logic in the counter module
            // based on current input values (clk, rst, en)
            // and update output values (count)
        }
        
        // Update control signals AFTER each complete clock cycle
        top->rst = (i<2) | (i==15);     
        // Reset logic: rst = 1 when i<2 OR i==15
        // PURPOSE: Test different scenarios to verify counter behavior
        // i=0,1: Initial reset (rst=1) - Test: Does counter reset to 0?
        // i=2-14: Normal operation (rst=0) - Test: Does counter work normally?
        // i=15: Mid-simulation reset (rst=1) - Test: Does counter reset during operation?
        // i=16-299: Normal operation (rst=0) - Test: Does counter continue after reset?
        
        top->en = (i>4);                
        // Enable logic: en = 1 when i>4
        // i=0-4: Counter disabled (en=0)
        // i=5-299: Counter enabled (en=1)
        
        // Check if simulation should terminate early
        if(Verilated::gotFinish()) exit(0);  
        // This allows external tools to signal early termination
    }

    // Cleanup
    tfp->close();  // Close the VCD trace file
    exit(0);       // Exit the program successfully
}
