#include "scoreboard.h"

scoreboard::scoreboard(uvm::uvm_component_name name) : 
  uvm::uvm_subscriber<result_transaction>(name), 
  cmd_f("cmd_f") {}

void scoreboard::predict_result(result_transaction& predicted, sequence_item& cmd){
  switch (cmd.op) {
    case op_t::add_op: predicted.result = cmd.A + cmd.B;
    case op_t::and_op: predicted.result = cmd.A & cmd.B;
    case op_t::xor_op: predicted.result = cmd.A ^ cmd.B;
    case op_t::mul_op: predicted.result = cmd.A * cmd.B;
  }
}

void scoreboard::write(const result_transaction& t){
  std::string data_str;
  sequence_item cmd;
  result_transaction predicted;
  do
    if(!cmd_f.nb_get(cmd))
      UVM_FATAL("SELF_CHECKER","Missing command in self checker");
  while((cmd.op == +op_t::no_op) || (cmd.op == +op_t::rst_op));
  predict_result(predicted,cmd);
  data_str = cmd.convert2string() +
    " ==>  Actual " +
    t.convert2string() +
    "/Predicted " +
    predicted.convert2string();
  if (!predicted.compare(t))
    UVM_ERROR("SELF_CHECKER", "FAIL: " + data_str);
  else
    UVM_INFO("SELF_CHECKER", "PASS: " + data_str, uvm::UVM_HIGH);
}
