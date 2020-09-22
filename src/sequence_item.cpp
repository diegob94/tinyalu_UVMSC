
#include "sequence_item.h"

sequence_item::sequence_item(const std::string& name = "") : uvm::uvm_sequence_item(name){}

void sequence_item::do_copy(const uvm::uvm_object& rhs){
    const sequence_item* _rhs = dynamic_cast<const sequence_item*>(&rhs);
    if(_rhs == NULL)
        UVM_FATAL("do_copy", "cast failed, check type compatability");
    uvm_sequence_item::do_copy(rhs);
    A = _rhs->A;
    B = _rhs->B;
    op = _rhs->op;
    result = _rhs->result;
}

bool sequence_item::do_compare(const uvm::uvm_object& rhs, const uvm::uvm_comparer* comparer){
    const sequence_item* _rhs = dynamic_cast<const sequence_item*>(&rhs);
    if(_rhs == NULL)
        UVM_FATAL("do_compare", "cast failed, check type compatibility");
    return uvm_sequence_item::do_compare(rhs,comparer) &&
        A == _rhs->A &&
        B == _rhs->B &&
        op == _rhs->op &&
        result == _rhs->result;
}

std::string sequence_item::convert2string(void){
    std::ostringstream str;
    str << "A: 0x" << std::hex << std::setw(2) << std::setfill('0') << A;
    str << "B: 0x" << std::hex << std::setw(2) << std::setfill('0') << B;
    str << "op: " << op_name(op);
    str << "result: 0x" << std::hex << std::setw(2) << std::setfill('0') << result;
    return str.str();
}
