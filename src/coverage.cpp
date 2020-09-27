#include "coverage.h"

coverage::coverage(uvm::uvm_component_name name) : 
    uvm::uvm_subscriber<sequence_item>(name), 
    op_set(op_t::no_op),
    op_cov_inst("op_cov_inst", this), 
    zeros_or_ones_on_ops_inst("zeros_or_ones_on_ops_inst", this) {}

void coverage::write(const sequence_item& t){
    A = t.A;
    B = t.B;
    op_set = t.op;
    op_cov_inst.sample();
    zeros_or_ones_on_ops_inst.sample();
}
