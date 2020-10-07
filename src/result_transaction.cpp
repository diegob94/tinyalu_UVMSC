
#include "result_transaction.h"

result_transaction::result_transaction(const std::string& name)
  : uvm_transaction(name)
  {}

void result_transaction::do_copy(const uvm::uvm_object& rhs){
    const result_transaction* _rhs = dynamic_cast<const result_transaction*>(&rhs);
    if(_rhs == NULL)
        UVM_FATAL("do_copy", "cast failed, check type compatability");
    uvm_transaction::do_copy(rhs);
    result = _rhs->result;
}

bool result_transaction::do_compare(const uvm::uvm_object& rhs, const uvm::uvm_comparer* comparer){
    const result_transaction* _rhs = dynamic_cast<const result_transaction*>(&rhs);
    if(_rhs == NULL)
        UVM_FATAL("do_compare", "cast failed, check type compatibility");
    return uvm_transaction::do_compare(rhs,comparer) &&
        result == _rhs->result;
}

std::string result_transaction::convert2string(void) const {
    std::ostringstream str;
    str << "result: 0x" << std::hex << std::setw(2) << std::setfill('0') << result;
    return str.str();
}
