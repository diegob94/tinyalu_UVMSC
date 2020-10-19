/*! \file sequence_item.h
    \brief UVM sequence item header
*/
#ifndef RESULT_TRANSACTION_H
#define RESULT_TRANSACTION_H

#include <iostream>
#include <iomanip>

#include <uvm>

class result_transaction : public uvm::uvm_transaction{
public:
    result_transaction(const std::string& name = "");
    UVM_OBJECT_UTILS(result_transaction);
    void do_copy(const uvm::uvm_object&);
    bool do_compare(const uvm::uvm_object&, const uvm::uvm_comparer*);
    std::string convert2string(void) const;
public:
    uint16_t result;
};

#endif // RESULT_TRANSACTION_H
