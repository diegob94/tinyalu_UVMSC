/*! \file top.cpp
    \brief top sc_module
*/
#include "top.h"

void top::stimulus(void){
//    test(4,3,add_op);
//    test(4,3,mul_op);
//    test(0,1,and_op);
    sc_stop();
}


top::top(sc_module_name) : top_clk ("top_clk", 10, SC_NS){
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
