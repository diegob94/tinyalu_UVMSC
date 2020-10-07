#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <uvm>
#include "tinyalu.h"
#include "result_transaction.h"
#include "sequence_item.h"

class scoreboard : public uvm::uvm_subscriber<result_transaction> {
  private:
    tlm::tlm_analysis_fifo<sequence_item> cmd_f;
  public:
    scoreboard(uvm::uvm_component_name);
    void predict_result(result_transaction&, sequence_item&);
    void write(const sequence_item&);
};

#endif // SCOREBOARD_H
