#ifndef TINYALU_BASE_TEST_H
#define TINYALU_BASE_TEST_H

#include <uvm>
#include "env.h"
#include "tinyalu.h"

class tinyalu_base_test : public uvm::uvm_test {
  public:
    UVM_COMPONENT_UTILS(tinyalu_base_test);
    tinyalu_base_test(uvm::uvm_component_name name = "");
    void build_phase(uvm::uvm_phase&);
    void end_of_elaboration_phase(uvm::uvm_phase&);
    sequencer* sequencer_p;
  private:
    env* env_p;
};

#endif // TINYALU_BASE_TEST_H
