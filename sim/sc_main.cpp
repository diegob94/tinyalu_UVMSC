#include <csignal>

#include <systemc>
#include <uvm>

#include <verilated.h>
#include <verilated_vcd_sc.h>

#include "Vtinyalu.h"
#include "Vtinyalu_tinyalu.h"

enum op_enum {
    no_op,
    add_op,
    and_op,
    xor_op,
    mul_op,
    rst_op
};

SC_MODULE(tinyalu_bfm){
    // Clock
    sc_in_clk clk{"clk"};
    // Input
    sc_signal<uint32_t> A{"A"};
    sc_signal<uint32_t> B{"B"};
    sc_signal<uint32_t> op{"op"};
    sc_signal<bool> reset_n{"reset_n"};
    sc_signal<bool> start{"start"};
    // Output
    sc_signal<bool> done{"done"};
    sc_signal<uint32_t> result{"result"};
    // Internal
    sc_in<bool> done_reg1{"done_reg1"};

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
            wait(done_reg1.value_changed_event());
            std::cout << sc_time_stamp() << ":bfn done_reg1: " << done_reg1 << std::endl;
        }
    }
    SC_CTOR(tinyalu_bfm){
        SC_THREAD(stimulus);
            sensitive << clk.pos();
        SC_THREAD(monitor_internal);
    }
};

SC_MODULE(top){
    Vtinyalu* dut;
    tinyalu_bfm* bfm;
    sc_clock top_clk{"top_clk"};

    sc_signal<bool> done_reg1;
    void sample_internal(void) {
        while(true){
            done_reg1 = dut->tinyalu->get_done_reg1();
            std::cout << sc_time_stamp() << ":top done_reg1: " << done_reg1 << std::endl;
            wait();
        }
    }
    
    SC_CTOR(top) : top_clk ("top_clk", 10, SC_NS){
        dut = new Vtinyalu("dut");
        bfm = new tinyalu_bfm("bfm");
        bfm->clk(top_clk);
        dut->clk(bfm->clk);
        dut->reset_n(bfm->reset_n);
        dut->A(bfm->A);
        dut->B(bfm->B);
        dut->op(bfm->op);
        dut->start(bfm->start);
        dut->done(bfm->done);
        dut->result(bfm->result);
        bfm->done_reg1(done_reg1);
        SC_THREAD(sample_internal);
            sensitive << bfm->clk.pos();
    }
};

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

