#include <iostream>
#include <sstream>
#include <string>

#ifndef ALGO_UTIL_FUNCS
#define ALGO_UTIL_FUNCS

namespace util_func {

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

// custom error logging
void err_log(const std::string &err, const bool &debug_flag);
void err_log(const std::string &err, const int &err_code,
             const bool &debug_flag);

} // namespace util_func
#endif