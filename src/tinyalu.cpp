/*! \file tinyalu.cpp
    \brief tinyalu utilities
*/
#include "tinyalu.h"

const std::string op_name(op_t op){
    switch(op){
        case op_t::no_op:
            return "no_op";
        case op_t::add_op:
            return "add_op"; 
        case op_t::and_op:
            return "and_op"; 
        case op_t::xor_op:
            return "xor_op"; 
        case op_t::mul_op:
            return "mul_op"; 
        case op_t::rst_op:
            return "rst_op"; 
    }
    return "unknown";
}
const uint32_t op_value(op_t op){
    return static_cast<typename std::underlying_type<op_t>::type>(op);
}
