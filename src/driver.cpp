#include "driver.h"

//template <typename REQ, typename RSP>
//driver<REQ,RSP>::driver(uvm::uvm_component_name name) : uvm::uvm_driver<REQ,RSP>( name ) {}
driver::driver(uvm::uvm_component_name name)
  : uvm::uvm_driver<sequence_item>( name ) 
  {}

//template <typename REQ, typename RSP>
//void driver<REQ,RSP>::build_phase(uvm::uvm_phase& phase){
void driver::build_phase(uvm::uvm_phase& phase){
    if(!uvm::uvm_config_db<tinyalu_bfm*>::get(NULL,"*","bfm",bfm)){
        UVM_FATAL("DRIVER","Failed to get bfm");
    }
}

//template <typename REQ, typename RSP>
//void driver<REQ,RSP>::run_phase(uvm::uvm_phase& phase){
void driver::run_phase(uvm::uvm_phase& phase){
    //REQ req;
    //RSP rsp;
    sequence_item req;
//    sequence_item rsp;
    for(;;) {
        this->seq_item_port->get_next_item(req); // or alternative this->seq_item_port->peek(req)
        bfm->send_op(req.A, req.B, req.op, req.result);
        UVM_INFO("DRIVER",req.convert2string(),uvm::UVM_FULL);
        this->seq_item_port->item_done();       // or alternative this->seq_item_port->get(tmp) to flush item from fifo
        //this->seq_item_port->put_response(rsp); // or alternative: this->seq_item_port->put(rsp)
    }
}
