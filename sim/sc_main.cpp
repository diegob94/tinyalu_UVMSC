#include <csignal>

#include <systemc>
#include <uvm>

#include <verilated.h>
#include <verilated_vcd_sc.h>

#include "Vtinyalu.h"
#include "Vtinyalu_tinyalu.h"

SC_MODULE(tb){
    Vtinyalu* dut;

    sc_clock tb_clk;

    // Input
    sc_in_clk clk;
    sc_signal<uint32_t> A;
    sc_signal<uint32_t> B;
    sc_signal<uint32_t> op;
    sc_signal<bool> reset_n;
    sc_signal<bool> start;
    // Output
    sc_signal<bool> done;
    sc_signal<uint32_t> result;
    // Internal
    sc_signal<bool> done_reg1;

    enum op_enum {no_op, add_op, and_op, xor_op, mul_op};

    void stimulus () {
        reset_n = 0;
        wait(10);
        reset_n = 1;
        wait();
        op_enum cmd_op = mul_op;
        A = 2;
        B = 4;
        op = cmd_op;
        start = 1;
        wait(done.posedge_event());
        std::cout << "Result: " << result << std::endl;
        wait(10);
        sc_stop();
    }

    void monitor_internal() {
        while(true){
            done_reg1 = dut->tinyalu->get_done_reg1();
            std::cout << "Monitor internal: " << done_reg1 << std::endl;
            wait();
        }
    }

    SC_CTOR(tb) : tb_clk ("clock", 10, SC_NS){
        dut = new Vtinyalu("dut");
        clk(tb_clk);
        dut->clk(clk);
        dut->reset_n(reset_n);
        dut->A(A);
        dut->B(B);
        dut->op(op);
        dut->start(start);
        dut->done(done);
        dut->result(result);
        SC_THREAD(stimulus);
            sensitive << clk.pos();
        SC_THREAD(monitor_internal);
            sensitive << clk.pos();
    }
};

tb* tb_p;
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
    tb_p = new tb("tb");
    const char* flag = Verilated::commandArgsPlusMatch("trace");
    if (flag && strcmp(flag, "+trace") == 0) {
        std::cout << "SC_MAIN: VCD open" << std::endl;
        tfp = new VerilatedVcdSc;
        tb_p->dut->trace(tfp, 99);
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

