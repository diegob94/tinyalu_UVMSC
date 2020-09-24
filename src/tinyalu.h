/*! \file tinyalu.h
    \brief tinyalu utilities header
*/
#ifndef TINYALU_H
#define TINYALU_H

#include <string>
#include <scv.h>

enum class op_t {
    no_op,
    add_op,
    and_op,
    xor_op,
    mul_op,
    rst_op
};

SCV_ENUM_EXTENSIONS(op_t) {
public:
    SCV_ENUM_CTOR(op_t){
        SCV_ENUM(op_t::no_op);
        SCV_ENUM(op_t::add_op);
        SCV_ENUM(op_t::and_op);
        SCV_ENUM(op_t::xor_op);
        SCV_ENUM(op_t::mul_op);
        SCV_ENUM(op_t::rst_op);
    }
};

#endif // TINYALU_H
