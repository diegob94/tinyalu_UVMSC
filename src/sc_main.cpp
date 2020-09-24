/*! \file sc_main.cpp
    \brief SystemC entry point
*/
#include <csignal>
#include <iomanip>
#include <iostream>

#include <systemc>
#include <uvm>

#include <verilated.h>
#include <verilated_vcd_sc.h>

#include "top.h"

top* top_p;
VerilatedVcdSc* tfp = nullptr;

void signal_handler(int signal) {
    if (signal == SIGABRT) {
        if (tfp) {
            tfp->flush();
        }
    }
    std::_Exit(EXIT_FAILURE);
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
    }
    std::signal(SIGABRT, signal_handler);
    sc_start();
    if (tfp) {
        std::cout << "SC_MAIN: VCD close" << std::endl;
        tfp->close();
    }
    return 0;
}


//#int sc_main(int argc, char* argv[]) {
//#    sc_start();
//#    ins_t inst = ins_t::SUB;
//#    std::cout<< "your instruction is: " << +scv_get_extensions(inst).get_integer() <<std::endl;
//#    std::cout<< "your instruction is: " << scv_get_extensions(inst).get_string() <<std::endl;
//#    scv_get_extensions(inst).assign(0);
//#    std::cout<< "now your instruction is: " << +scv_get_extensions(inst).get_integer() <<std::endl;
//#    std::cout<< "now your instruction is: " << scv_get_extensions(inst).get_string() <<std::endl;
//#    sc_stop();
//#    return 0;
//#}


