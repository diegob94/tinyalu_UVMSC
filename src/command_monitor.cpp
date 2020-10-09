#include "command_monitor.h"
#include "tinyalu_bfm.h"

command_monitor::command_monitor(uvm::uvm_component_name name) 
  : uvm_component(name) 
  {}

void command_monitor::build_phase(uvm::uvm_phase& phase){
    if(!uvm::uvm_config_db<tinyalu_bfm*>::get(NULL,"*","bfm",bfm)){
        UVM_FATAL("DRIVER","Failed to get bfm");
    }
}

void command_monitor::connect_phase(uvm::uvm_phase& phase){
    bfm->command_monitor_p = this;
}
