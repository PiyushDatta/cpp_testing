#include <iostream>
#include <string>
#include <sstream>
#pragma once

namespace UtilFunc {

// our custom std::to_string, since this function doesn't work for all compilers
// template <typename T> std::string custom_to_string(const T &value);
template <typename T> std::string custom_to_string(const T &value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}

// custom debug logging
void debug_log(const std::string &debug_string, const bool &debug_flag);
void debug_log(const std::string &debug_string, const int &debug_int,
               const bool &debug_flag);

} // namespace UtilFunc
