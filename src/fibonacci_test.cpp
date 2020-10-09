#include "fibonacci_test.h"

fibonacci_test::fibonacci_test(uvm::uvm_component_name name)
  : tinyalu_base_test(name)
  {}

void fibonacci_test::run_phase(uvm::uvm_phase& phase) {
  fibonacci_sequence fibonacci("fibonacci");
  phase.raise_objection(this);
  fibonacci.start(sequencer_p);
  phase.drop_objection(this);
}
