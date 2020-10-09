#include "fibonacci_sequence.h"

fibonacci_sequence::fibonacci_sequence(const std::string& name)
  : uvm::uvm_sequence<sequence_item>(name)
  {}

void fibonacci_sequence::body(void) {
  uint8_t n_minus_2=0;
  uint8_t n_minus_1=1;
  sequence_item* command;
  command = sequence_item::type_id::create("command");
  start_item(command);
  command->op = op_t::rst_op;
  finish_item(command);
  UVM_INFO("FIBONACCI", " Fib(01) = 00", uvm::UVM_MEDIUM);
  UVM_INFO("FIBONACCI", " Fib(02) = 01", uvm::UVM_MEDIUM);
  for(int ff = 3; ff<=14; ff++) {
    start_item(command);
    command->A = n_minus_2;
    command->B = n_minus_1;
    command->op = op_t::add_op;
    finish_item(command);
    n_minus_2 = n_minus_1;
    n_minus_1 = command->result;
    std::ostringstream msg;
    msg << "Fib(" << ff << " = " << n_minus_1;
    UVM_INFO("FIBONACCI", msg.str(), uvm::UVM_MEDIUM);
  }
}
