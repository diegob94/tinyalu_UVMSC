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

void command_monitor::write_to_monitor(uint8_t A, uint8_t B, op_t op){
  sequence_item* cmd;
  cmd = sequence_item::type_id::create("cmd");
  cmd->A = A;
  cmd->B = B;
  cmd->op = op;
  UVM_INFO("COMMAND_MONITOR", cmd->convert2string(), uvm::UVM_HIGH);
  ap.write(*cmd);
}
