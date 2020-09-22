/*! \file sequence_item.h
    \brief UVM sequence item header
*/
#ifndef SEQUENCE_ITEM_H
#define SEQUENCE_ITEM_H

#include <iostream>
#include <iomanip>

#include <uvm>

#include "tinyalu.h"

class sequence_item : public uvm::uvm_sequence_item{
public:
    sequence_item(const std::string&);
    UVM_OBJECT_UTILS(sequence_item);
    void do_copy(const uvm::uvm_object&);
    bool do_compare(const uvm::uvm_object&, const uvm::uvm_comparer*);
    std::string convert2string(void);
public:
    uint8_t A;
    uint8_t B;
    uint16_t result;
    op_t op;
};

#endif // SEQUENCE_ITEM_H
