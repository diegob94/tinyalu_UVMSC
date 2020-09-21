/*! \file tinyalu.cpp
    \brief tinyalu utilities
*/
#include "tinyalu.h"

const char * op_name(operation_t op){
    switch(op){
        case no_op:
            return "no_op";
        case add_op:
            return "add_op"; 
        case and_op:
            return "and_op"; 
        case xor_op:
            return "xor_op"; 
        case mul_op:
            return "mul_op"; 
        case rst_op:
            return "rst_op"; 
    }
    return "unknown";
}
