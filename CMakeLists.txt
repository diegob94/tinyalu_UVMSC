cmake_minimum_required(VERSION 3.8)

project(tinyalu)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(RTL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rtl)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(RTL_FILES ${RTL_DIR}/tinyalu.v)
file(GLOB_RECURSE SYSTEMC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

add_executable(sim ${SYSTEMC_FILES})

message(STATUS "RTL_FILES=${RTL_FILES}")
message(STATUS "SYSTEMC_FILES=${SYSTEMC_FILES}")

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})
if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found. Either install it, or set the VERILATOR_ROOT environment variable")
endif()

if(NOT DEFINED ENV{SYSTEMC_INCLUDE})
    message(FATAL_ERROR "SYSTEMC_INCLUDE environment variable not defined")
endif()
set(SYSTEMC_INCLUDE $ENV{SYSTEMC_INCLUDE})
message(STATUS "SYSTEMC_INCLUDE=${SYSTEMC_INCLUDE}")

if(NOT DEFINED ENV{SYSTEMC_LIBDIR})
    message(FATAL_ERROR "SYSTEMC_LIBDIR environment variable not defined")
endif()
set(SYSTEMC_LIBDIR $ENV{SYSTEMC_LIBDIR})
message(STATUS "SYSTEMC_LIBDIR=${SYSTEMC_LIBDIR}")

set(UVM_SYSTEMC_LIBDIR ${SYSTEMC_LIBDIR})
set(UVM_SYSTEMC_INCLUDE ${SYSTEMC_INCLUDE})
find_library(LIB_UVM_SYSTEMC uvm-systemc ${UVM_SYSTEMC_LIBDIR})
message(STATUS "LIB_UVM_SYSTEMC=${LIB_UVM_SYSTEMC}")
target_link_libraries(sim PRIVATE ${LIB_UVM_SYSTEMC})
target_include_directories(sim PRIVATE ${UVM_SYSTEMC_INCLUDE})

set(SYSTEMC_VERIF_LIBDIR ${SYSTEMC_LIBDIR})
set(SYSTEMC_VERIF_INCLUDE ${SYSTEMC_INCLUDE})
find_library(LIB_SYSTEMC_VERIF scv ${SYSTEMC_VERIF_LIBDIR})
message(STATUS "LIB_SYSTEMC_VERIF=${LIB_SYSTEMC_VERIF}")
target_link_libraries(sim PRIVATE ${LIB_SYSTEMC_VERIF})
target_include_directories(sim PRIVATE ${SYSTEMC_VERIF_INCLUDE})

# SystemC dependencies
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#set(CMAKE_PREFIX_PATH /home/diegob/eda)
find_package(SystemCLanguage CONFIG REQUIRED)

find_package(fc4sc CONFIG REQUIRED)
target_link_libraries(sim PRIVATE fc4sc)

verilate(sim TRACE SYSTEMC SOURCES ${RTL_FILES} INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/verilog VERILATOR_ARGS -Wno-fatal --timescale 1ns/1ps)
verilator_link_systemc(sim)

option(BUILD_DOC "Build documentation" OFF)

if (BUILD_DOC)
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
endif (BUILD_DOC)
