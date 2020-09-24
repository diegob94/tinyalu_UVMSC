/*! \file tinyalu_bfm.cpp
    \brief tinyalu bus functional model
*/
#include "tinyalu_bfm.h"

tinyalu_bfm::tinyalu_bfm(sc_core::sc_module_name name) : sc_module(name) {}

void tinyalu_bfm::send_op(uint8_t iA, uint8_t iB, op_t iop, uint16_t &alu_result){
    op = scv_get_extensions(iop).get_integer();
    if (iop == op_t::rst_op) {
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
        if (iop == op_t::no_op) {
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

void tinyalu_bfm::reset_op(void) {
    reset_n = 0;
    wait(clk.negedge_event());
    reset_n = 1;
    start = 1;
}

void tinyalu_bfm::op_monitor_thread(void){
//    bool in_command = 0;
//    if(start) {
//        if(!in_command){
//            command_monitor_p->write_to_monitor(A,B);
//        }
//    }
}

void tinyalu_bfm::rst_monitor_thread(void){
}

void tinyalu_bfm::result_monitor_thread(void){

}
