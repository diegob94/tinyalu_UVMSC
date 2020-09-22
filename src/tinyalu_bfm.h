/*! \file tinyalu_bfm.h
    \brief tinyalu bus functional model header
*/
#ifndef TINYALU_BFM_H
#define TINYALU_BFM_H

#include <systemc>
#include "tinyalu.h"

//! \todo bus protocol assertions

SC_MODULE(tinyalu_bfm){
    // Clock
    sc_core::sc_in_clk clk{"clk"};
    // Input
    sc_core::sc_signal<uint32_t> A{"A"};
    sc_core::sc_signal<uint32_t> B{"B"};
    sc_core::sc_signal<uint32_t> op{"op"};
    sc_core::sc_signal<bool> reset_n{"reset_n"};
    sc_core::sc_signal<bool> start{"start"};
    // Output
    sc_core::sc_signal<bool> done{"done"};
    sc_core::sc_signal<uint32_t> result{"result"};

    SC_CTOR(tinyalu_bfm);
    void reset_op(void);
    void send_op(uint8_t, uint8_t, op_t, uint16_t&);
};

#endif // TINYALU_BFM_H
