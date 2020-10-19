#ifndef RESULT_MONITOR_H
#define RESULT_MONITOR_H

#include <uvm>
#include "result_transaction.h"

class tinyalu_bfm;

class result_monitor : public uvm::uvm_component {
public:
    UVM_COMPONENT_UTILS(result_monitor);
    result_monitor(uvm::uvm_component_name);
    void build_phase(uvm::uvm_phase&);
    void connect_phase(uvm::uvm_phase&);
    void write_to_monitor(uint16_t);
    uvm::uvm_analysis_port<result_transaction> ap;
private:
    tinyalu_bfm* bfm;
};

#endif // RESULT_MONITOR_H
