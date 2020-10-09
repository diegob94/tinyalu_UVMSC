/*! \file top.h
    \brief top sc_module header
*/
#ifndef TOP_H
#define TOP_H

#include <systemc>
#include "Vtinyalu.h"
#include "tinyalu_bfm.h"
#include "env.h"

SC_MODULE(top){
    Vtinyalu* dut;
    sc_clock top_clk{"top_clk"};
public:
    tinyalu_bfm* bfm;
    SC_CTOR(top);
};

#endif // TOP_H
