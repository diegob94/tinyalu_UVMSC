# \todo add include path

find_library(LIB_SYSTEMC_VERIF scv ${SYSTEMC_VERIF_LIBDIR})
message(STATUS "LIB_SYSTEMC_VERIF=${LIB_SYSTEMC_VERIF}")
link_libraries(${LIB_SYSTEMC_VERIF})
include_directories(${SYSTEMC_VERIF_INCLUDE})
