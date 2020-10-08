#include "env.h"


env::env(uvm::uvm_component_name name) 
  : uvm::uvm_env(name)
  {};

void env::build_phase(uvm::uvm_phase&) {
  // stimulus
  sequencer_p  = new sequencer("sequencer_p");
  driver_p     = driver::type_id::create("driver_p",this);
  // monitors
  command_monitor_p = command_monitor::type_id::create("command_monitor_p",this);
  result_monitor_p  = result_monitor::type_id::create("result_monitor_p",this);
  // analysis
  coverage_p    = coverage::type_id::create ("coverage_p",this);
  scoreboard_p  = scoreboard::type_id::create("scoreboard_p",this);
}

void env::connect_phase(uvm::uvm_phase&) {
  driver_p->seq_item_port.connect(sequencer_p->seq_item_export);
  command_monitor_p->ap.connect(coverage_p->analysis_export);
  command_monitor_p->ap.connect(scoreboard_p->cmd_f);
  result_monitor_p->ap.connect(scoreboard_p->analysis_export);
}
