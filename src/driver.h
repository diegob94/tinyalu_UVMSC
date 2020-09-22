/*! \file driver.h
    \brief UVM driver header
*/
#ifndef DRIVER_H
#define DRIVER_H

#include <uvm>

#include "tinyalu_bfm.h"

using namespace uvm;

template <typename REQ = uvm_sequence_item, typename RSP = REQ>
class driver : public uvm_driver<REQ,RSP>{
public:
    driver(uvm_component_name);
    void build_phase(uvm_phase&);
    void run_phase(uvm_phase&);
private:
    tinyalu_bfm* bfm;
    int data_array[512];
};

#endif // DRIVER_H
