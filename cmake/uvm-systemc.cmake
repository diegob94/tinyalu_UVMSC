# \todo add include path

find_library(LIB_UVM_SYSTEMC uvm-systemc ${UVM_SYSTEMC_LIBDIR})
message(STATUS "LIB_UVM_SYSTEMC=${LIB_UVM_SYSTEMC}")
link_libraries(${LIB_UVM_SYSTEMC})
include_directories(${UVM_SYSTEMC_INCLUDE})
