#include "result_monitor.h"
#include "tinyalu_bfm.h"

result_monitor::result_monitor(uvm::uvm_component_name name) : uvm_component(name) {}

void result_monitor::build_phase(uvm::uvm_phase& phase){
    if(!uvm::uvm_config_db<tinyalu_bfm*>::get(NULL,"*","bfm",bfm)){
        UVM_FATAL("DRIVER","Failed to get bfm");
    }
}

void result_monitor::connect_phase(uvm::uvm_phase& phase){
    bfm->result_monitor_p = this;
}
