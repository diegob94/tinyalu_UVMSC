#include "driver.h"

template <typename REQ, typename RSP>
driver<REQ,RSP>::driver(uvm_component_name name) : uvm_driver<REQ,RSP>( name ) {}

template <typename REQ, typename RSP>
void driver<REQ,RSP>::build_phase(uvm_phase& phase){
    if(uvm_config_db<tinyalu_bfm*>::get(NULL,"*","bfm",bfm)){
        UVM_FATAL("DRIVER","Failed to get bfm");
    }
}

template <typename REQ, typename RSP>
void driver<REQ,RSP>::run_phase(uvm_phase& phase){
    REQ req;
    RSP rsp;
    for(;;) {
        uint8_t result;
        this->seq_item_port->get_next_item(req); // or alternative this->seq_item_port->peek(req)
        bfm->send_op(req->A, req->B, req->op, result);
        req->result = result;
        this->seq_item_port->item_done();       // or alternative this->seq_item_port->get(tmp) to flush item from fifo
        //this->seq_item_port->put_response(rsp); // or alternative: this->seq_item_port->put(rsp)
    }
}
