#include <csignal>
#include <iomanip>
#include <iostream>

#include <systemc>
#include <uvm>

#include <verilated.h>
#include <verilated_vcd_sc.h>

#include "Vtinyalu.h"

enum operation_t {
    no_op,
    add_op,
    and_op,
    xor_op,
    mul_op,
    rst_op
};

const char * op_name(operation_t op){
    switch(op){
        case no_op:
            return "no_op";
        case add_op:
            return "add_op"; 
        case and_op:
            return "and_op"; 
        case xor_op:
            return "xor_op"; 
        case mul_op:
            return "mul_op"; 
        case rst_op:
            return "rst_op"; 
    }
    return "unknown";
}

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

    void reset_op () {
        reset_n = 0;
        wait(clk.negedge_event());
        reset_n = 1;
        start = 1;
    }
    void send_op(uint8_t iA, uint8_t iB, operation_t iop, uint16_t &alu_result){
        op = iop;
        if (iop == rst_op) {
            wait(clk.posedge_event());
            reset_n = 0;
            start = 0;
            wait(clk.posedge_event());
            reset_n = 1;
        } else {
            wait(clk.negedge_event());
            A = iA;
            B = iB;
            start = 1;
            if (iop == no_op) {
                wait(clk.posedge_event());
                start = 0;           
            } else {
                do
                    wait(clk.negedge_event());
                while (done == 0);
                alu_result = result;
                start = 0;
            }
        }
    }

    SC_CTOR(tinyalu_bfm){
    }
};

SC_MODULE(top){
    Vtinyalu* dut;
    tinyalu_bfm* bfm;
    sc_clock top_clk{"top_clk"};
    
    void stimulus(){
        test(4,3,add_op);
        test(4,3,mul_op);
        test(0,1,and_op);
        sc_stop();
    }

    void test(uint8_t A, uint8_t B, operation_t op){
        uint16_t result = 0;
        std::cout << std::setfill(' ') << std::setw(20) << sc_time_stamp() << ": reset_op" << std::endl;
        bfm->reset_op();
        std::cout << std::setfill(' ') << std::setw(20) << sc_time_stamp() << ": send_op A=" << +A << " B=" << +B << " op=" << op_name(op) << std::endl;
        bfm->send_op(A,B,op,result);
        std::cout << std::setfill(' ') << std::setw(20) << sc_time_stamp() << ": result="<< result << std::endl;
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
        SC_THREAD(stimulus);
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

