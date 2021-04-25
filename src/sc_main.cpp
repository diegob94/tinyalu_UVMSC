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

top* top_p;
VerilatedVcdSc* tfp = nullptr;

void exit_handler() {
  std::cout << "SC_MAIN: flushing VCD buffer" << std::endl;
  if (tfp) {
    tfp->flush();
    tfp->close();
  }
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
    tfp->open("tb_v0.vcd");
    std::atexit(exit_handler);
  }
  uvm::uvm_set_verbosity_level(uvm::UVM_FULL);
  uvm::uvm_config_db<tinyalu_bfm*>::set(NULL,"*","bfm",top_p->bfm);
  uvm::run_test("fibonacci_test");
  return 0;
}


