#include <iostream>
#include <algorithm>
#include <regex>

#include <systemc>

#include "sc_trace_util.h"

using namespace sc_core;

void print_sc_trace(const char * s, const char * kind, size_t depth) {
  std::regex e ("^top");
  std::regex e1 ("\\.");
  std::string obj = std::regex_replace(std::regex_replace(s,e,"top_p"),e1,"->");
  std::cout << "sc_trace(tf," << obj << ",\"" << s << "\"); // kind: " << kind;
  if (depth != -1) {
    std::cout << " depth: " << depth;
  }
  std::cout << std::endl;
}

void _generate_trace_code(sc_object* obj, size_t depth = 1) {
  if (depth == 0) {
    return;
  }
  std::vector<std::string> trace_types = {"sc_in", "sc_out", "sc_clock", "sc_signal"};
  const char* kind = nullptr;
  for ( auto child : obj->get_child_objects() ) {
    if ( child ) {
      kind = child->kind();
      if (std::find(trace_types.begin(), trace_types.end(), kind) != trace_types.end()) {
        print_sc_trace(child->name(),kind,depth);
      }
      _generate_trace_code(child, depth == -1 ? depth : depth - 1);
    }
  }
}

void generate_trace_code(size_t depth) {
  std::cout << std::endl;
  for (auto tops : sc_get_top_level_objects()) {
    if (tops) {
      std::cout << "// top hierarchy: " << tops->name() << std::endl;
      _generate_trace_code(tops, depth); 
    }
  }
  std::cout << std::endl;
}
