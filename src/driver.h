/*! \file driver.h
    \brief UVM driver header
*/
#ifndef DRIVER_H
#define DRIVER_H

#include <uvm>

using namespace uvm;

template <typename REQ = uvm_sequence_item, typename RSP = REQ>
class driver : public uvm_driver<REQ,RSP>{
public:
    driver(uvm_component_name);
    UVM_COMPONENT_PARAM_UTILS(driver<REQ,RSP>);
    void run_phase(uvm_phase&);
private:
    int data_array[512];
};

#endif // DRIVER_H
