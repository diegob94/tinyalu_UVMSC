/*! \file driver.cpp
    \brief UVM driver
*/
#include "driver.h"

driver::driver( uvm::uvm_component_name name ) : uvm::uvm_driver<REQ,RSP>( name ) {}

void driver::run_phase(uvm::uvm_phase& phase){
    REQ req;
    RSP rsp;
    for(;;) {
        this->seq_item_port->get_next_item(req); // or alternative this->seq_item_port->peek(req)
        rsp.set_id_info(req);

        // Actually do the read or write here
        if (req.op == BUS_READ)
        {
        rsp.addr = req.addr;
        rsp.data = data_array[rsp.addr];
        UVM_INFO("my_driver", rsp.convert2string(), UVM_MEDIUM);
        }
        else // req.op == BUS_WRITE
        {
        data_array[req.addr] = req.data;
        UVM_INFO("my_driver", req.convert2string(), UVM_MEDIUM);
        }

        this->seq_item_port->item_done();       // or alternative this->seq_item_port->get(tmp) to flush item from fifo
        this->seq_item_port->put_response(rsp); // or alternative: this->seq_item_port->put(rsp)
    }
}


