// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter.h for the primary calling header

#include "verilated.h"

#include "Vcounter___024root.h"

VL_INLINE_OPT void Vcounter___024root___sequent__TOP__0(Vcounter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused variable warnings
    Vcounter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter___024root___sequent__TOP__0\n"); );
    // Body - This function implements the counter logic from counter.sv
    vlSelf->count = ((IData)(vlSelf->rst) ? 0U : (0xffU 
                                                  & ((IData)(vlSelf->count) 
                                                     + (IData)(vlSelf->en))));
    // COUNTER LOGIC BREAKDOWN:
    // vlSelf->rst ? 0U : ... = If reset is active, set count to 0
    // Otherwise: count = count + en (with 8-bit masking)
    // 0xffU = 11111111 in binary = 8-bit mask to prevent overflow
    // This translates the SystemVerilog: if (rst) count <= 0; else count <= count + en;
}

void Vcounter___024root___eval(Vcounter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused variable warnings
    Vcounter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter___024root___eval\n"); );
    // Body - This function detects clock edges and triggers sequential logic
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vcounter___024root___sequent__TOP__0(vlSelf);
    }
    // CLOCK EDGE DETECTION BREAKDOWN:
    // vlSelf->clk = Current clock value
    // vlSelf->__Vclklast__TOP__clk = Previous clock value (stored)
    // ~ (NOT) = Bitwise complement
    // & (AND) = Bitwise AND
    // Logic: current_clk AND (NOT previous_clk) = Rising edge detection
    // Example: clk=1, prev_clk=0 → 1 & (~0) = 1 & 1 = 1 (TRUE - Rising edge!)
    //          clk=0, prev_clk=1 → 0 & (~1) = 0 & 0 = 0 (FALSE - Not rising edge)
    // This translates the SystemVerilog: always_ff @ (posedge clk)
    
    // Final - Store current clock value for next edge detection
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

#ifdef VL_DEBUG
void Vcounter___024root___eval_debug_assertions(Vcounter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused variable warnings
    Vcounter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter___024root___eval_debug_assertions\n"); );
    // Body - Debug assertions to check signal widths
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    // DEBUG ASSERTION BREAKDOWN:
    // 0xfeU = 11111110 in binary (all bits except bit 0)
    // clk & 0xfeU = Check if any bit other than bit 0 is set
    // If true, clk is wider than 1 bit (ERROR!)
    // This ensures clk is exactly 1 bit as declared in SystemVerilog
    
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    // Same check for rst signal - must be exactly 1 bit
    
    if (VL_UNLIKELY((vlSelf->en & 0xfeU))) {
        Verilated::overWidthError("en");}
    // Same check for en signal - must be exactly 1 bit
}
#endif  // VL_DEBUG
