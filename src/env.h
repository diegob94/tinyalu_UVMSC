#ifndef ENV_H
#define ENV_H

#include <uvm>
#include "tinyalu.h"
#include "coverage.h"
#include "scoreboard.h"
#include "driver.h"
#include "command_monitor.h"
#include "result_monitor.h"

class env : public uvm::uvm_env {
public:
  UVM_COMPONENT_UTILS(env);
  env(uvm::uvm_component_name name = "");
  void build_phase(uvm::uvm_phase&);
  void connect_phase(uvm::uvm_phase&);
private:
  sequencer*       sequencer_p;
  coverage*        coverage_p;
  scoreboard*      scoreboard_p;
  driver*          driver_p;
  command_monitor* command_monitor_p;
  result_monitor*  result_monitor_p; 
};

#endif // ENV_H
