#ifndef FIBONACCI_TEST_H
#define FIBONACCI_TEST_H

#include "tinyalu_base_test.h"
#include "fibonacci_sequence.h"

class fibonacci_test : public tinyalu_base_test {
  public:
    UVM_COMPONENT_UTILS(fibonacci_test);
    fibonacci_test(uvm::uvm_component_name name = "");
    void run_phase(uvm::uvm_phase&);
};

#endif // FIBONACCI_TEST_H
