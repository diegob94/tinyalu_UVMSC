/*! \file tinyalu.h
    \brief tinyalu utilities header
*/
#ifndef TINYALU_H
#define TINYALU_H

#include <string>

enum class op_t {
    no_op,
    add_op,
    and_op,
    xor_op,
    mul_op,
    rst_op
};

//! \todo create enum class for encapsulation?
const std::string op_name(op_t);
const uint32_t op_value(op_t);

#endif // TINYALU_H
