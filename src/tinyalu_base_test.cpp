#include "tinyalu_base_test.h"

tinyalu_base_test::tinyalu_base_test(uvm::uvm_component_name name) 
  : uvm::uvm_test(name) 
  {}

void tinyalu_base_test::build_phase(uvm::uvm_phase&) {
  env_p = env::type_id::create("env_p",this);
}

void tinyalu_base_test::end_of_elaboration_phase(uvm::uvm_phase&) {
  sequencer_p = env_p->sequencer_p;
}
