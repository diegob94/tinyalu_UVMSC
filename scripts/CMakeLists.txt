cmake_minimum_required(VERSION 3.8)

project(tinyalu)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(RTL_DIR ${ROOT}/rtl)
set(SIM_DIR ${ROOT}/sim)

set(RTL_FILES ${RTL_DIR}/tinyalu.v)

message(STATUS "ROOT=${ROOT}")
message(STATUS "RTL_FILES=${RTL_FILES}")

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})
if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found. Either install it, or set the VERILATOR_ROOT environment variable")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/uvm-systemc.cmake)

# SystemC dependencies
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#set(CMAKE_PREFIX_PATH /home/diegob/eda)
find_package(SystemCLanguage CONFIG REQUIRED)

add_executable(sim ${SIM_DIR}/sc_main.cpp)

verilate(sim TRACE SYSTEMC SOURCES ${RTL_FILES} INCLUDE_DIRS ${SIM_DIR}/include VERILATOR_ARGS -Wno-fatal --timescale 1ns/1ps)
verilator_link_systemc(sim)

####################################################################################################################################

#set(SYSTEMC_LIBDIR $ENV{SYSTEMC_LIBDIR})
#set(SYSTEMC_INCLUDE $ENV{SYSTEMC_INCLUDE})
#find_library(LIB_SYSTEMC systemc ${SYSTEMC_LIBDIR})
#
#message(STATUS "SYSTEMC_LIBDIR=${SYSTEMC_LIBDIR}")
#message(STATUS "SYSTEMC_INCLUDE=${SYSTEMC_INCLUDE}")
#message(STATUS "LIB_SYSTEMC=${LIB_SYSTEMC}")
#
#link_libraries(${LIB_SYSTEMC})
#include_directories(${SYSTEMC_INCLUDE})
#
#file(GLOB SOURCES "*.cpp")
#file(GLOB HEADERS "*.h")
#
#add_executable(${PROJECT_NAME} hello_world.cpp)
#
#option(BUILD_DOC "Build documentation" ON)
#
#find_package(Doxygen)
#if (DOXYGEN_FOUND)
#    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
#    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
#    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#    message("Doxygen build started")
#    add_custom_target( doc_doxygen ALL
#        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        COMMENT "Generating API documentation with Doxygen"
#        VERBATIM )
#else (DOXYGEN_FOUND)
#  message("Doxygen need to be installed to generate the doxygen documentation")
#endif (DOXYGEN_FOUND)

