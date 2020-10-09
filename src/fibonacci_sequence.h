#ifndef FIBONACCI_SEQUENCE
#define FIBONACCI_SEQUENCE

#include <uvm>
#include "sequence_item.h"

class fibonacci_sequence : public uvm::uvm_sequence<sequence_item> {
  public:
    UVM_OBJECT_UTILS(fibonacci_sequence);
    fibonacci_sequence(const std::string& name = "");
    void body(void);
};

#endif // FIBONACCI_SEQUENCE
