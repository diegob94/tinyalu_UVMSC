/*! \file tinyalu.h
    \brief tinyalu utilities header
*/
#ifndef TINYALU_H
#define TINYALU_H

#include <enum.h>
#include <uvm>

BETTER_ENUM(op_t, uint32_t,no_op,add_op,and_op,xor_op,mul_op,rst_op);

class sequence_item;
typedef uvm::uvm_sequencer<sequence_item> sequencer;

#endif // TINYALU_H
