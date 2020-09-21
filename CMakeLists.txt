cmake_minimum_required(VERSION 3.8)

project(tinyalu)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(RTL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rtl)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(RTL_FILES ${RTL_DIR}/tinyalu.v)
file(GLOB_RECURSE SYSTEMC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

message(STATUS "RTL_FILES=${RTL_FILES}")

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})
if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found. Either install it, or set the VERILATOR_ROOT environment variable")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/uvm-systemc.cmake)

# SystemC dependencies
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#set(CMAKE_PREFIX_PATH /home/diegob/eda)
find_package(SystemCLanguage CONFIG REQUIRED)

add_executable(sim ${SYSTEMC_FILES})

verilate(sim TRACE SYSTEMC SOURCES ${RTL_FILES} INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/verilog VERILATOR_ARGS -Wno-fatal --timescale 1ns/1ps)
verilator_link_systemc(sim)

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
