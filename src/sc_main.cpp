/*! \file sc_main.cpp
    \brief SystemC entry point
*/
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include <systemc>
#include <uvm>

#include <verilated.h>
#include <verilated_vcd_sc.h>

#include "top.h"
#include "sc_trace_util.h"

top* top_p;
VerilatedVcdSc* tfp = nullptr;

void exit_handler() {
  std::cout << "SC_MAIN: flushing VCD buffer" << std::endl;
  if (tfp) {
    tfp->flush();
    tfp->close();
  }
}

void trace_sc(sc_trace_file* tf, top* top_p) {
  // top hierarchy: top
  sc_trace(tf,top_p->top_clk,"top.top_clk"); // kind: sc_clock
  sc_trace(tf,top_p->dut->A,"top.dut.A"); // kind: sc_in
  sc_trace(tf,top_p->dut->B,"top.dut.B"); // kind: sc_in
  sc_trace(tf,top_p->dut->op,"top.dut.op"); // kind: sc_in
  sc_trace(tf,top_p->dut->clk,"top.dut.clk"); // kind: sc_in
  sc_trace(tf,top_p->dut->reset_n,"top.dut.reset_n"); // kind: sc_in
  sc_trace(tf,top_p->dut->start,"top.dut.start"); // kind: sc_in
  sc_trace(tf,top_p->dut->done,"top.dut.done"); // kind: sc_out
  sc_trace(tf,top_p->dut->result,"top.dut.result"); // kind: sc_out
  sc_trace(tf,top_p->bfm->clk,"top.bfm.clk"); // kind: sc_in
  sc_trace(tf,top_p->bfm->A,"top.bfm.A"); // kind: sc_signal
  sc_trace(tf,top_p->bfm->B,"top.bfm.B"); // kind: sc_signal
  sc_trace(tf,top_p->bfm->op,"top.bfm.op"); // kind: sc_signal
  sc_trace(tf,top_p->bfm->reset_n,"top.bfm.reset_n"); // kind: sc_signal
  sc_trace(tf,top_p->bfm->start,"top.bfm.start"); // kind: sc_signal
  sc_trace(tf,top_p->bfm->done,"top.bfm.done"); // kind: sc_signal
  sc_trace(tf,top_p->bfm->result,"top.bfm.result"); // kind: sc_signal
}

int sc_main(int argc, char* argv[]) {
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  sc_set_time_resolution(1, SC_PS);
  top_p = new top("top");
  const char* flag = Verilated::commandArgsPlusMatch("trace");
  if (flag && strcmp(flag, "+trace") == 0) {
    std::cout << "SC_MAIN: VCD open" << std::endl;
    tfp = new VerilatedVcdSc;
    top_p->dut->trace(tfp, 99);
    tfp->open("tb_vlt.vcd");
    std::atexit(exit_handler);
    sc_trace_file* tf = sc_create_vcd_trace_file("tb_sc");
    trace_sc(tf, top_p);
  }
  flag = Verilated::commandArgsPlusMatch("gen_trace_code");
  if (flag && strcmp(flag, "+gen_trace_code") == 0) {
    generate_trace_code();
    return 0;
  }
  uvm::uvm_set_verbosity_level(uvm::UVM_FULL);
  uvm::uvm_config_db<tinyalu_bfm*>::set(NULL,"*","bfm",top_p->bfm);
  uvm::run_test("fibonacci_test");
  return 0;
}


