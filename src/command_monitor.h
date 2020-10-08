#ifndef COMMAND_MONITOR_H
#define COMMAND_MONITOR_H

#include <uvm>
#include "tinyalu.h"
#include "sequence_item.h"

class tinyalu_bfm;

class command_monitor : public uvm::uvm_component {
  public:
    UVM_COMPONENT_UTILS(command_monitor);
    command_monitor(uvm::uvm_component_name);
    void build_phase(uvm::uvm_phase&);
    void connect_phase(uvm::uvm_phase&);
    void write_to_monitor(uint8_t A, uint8_t B, op_t op);
    uvm::uvm_analysis_port<sequence_item> ap;
  private:
    tinyalu_bfm* bfm;
};

#endif // COMMAND_MONITOR_H
