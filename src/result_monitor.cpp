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

void result_monitor::write_to_monitor(uint16_t result){
  result_transaction* result_t;
  result_t = result_transaction::type_id::create("result_t");
  result_t->result = result;
  UVM_INFO("RESULT_MONITOR", result_t->convert2string(), uvm::UVM_HIGH);
  ap.write(*result_t);
}
