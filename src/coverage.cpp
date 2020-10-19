#include "coverage.h"

coverage::coverage(uvm::uvm_component_name name) : 
    uvm::uvm_subscriber<sequence_item>(name), 
    op_cov_inst("op_cov_inst"),
    zeros_or_ones_on_ops_inst("zeros_or_ones_on_ops_inst") {}

void coverage::write(const sequence_item& t){
    op_cov_inst.op_set = t.op;
    zeros_or_ones_on_ops_inst.A = t.A;
    zeros_or_ones_on_ops_inst.B = t.B;
    zeros_or_ones_on_ops_inst.op_set = t.op;
    op_cov_inst.sample();
    zeros_or_ones_on_ops_inst.sample();
}
