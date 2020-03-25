#include "include/util_functions.h"

namespace util_func {

void debug_log(const std::string &debug_string, const bool &debug_flag) {
  if (debug_flag) {
    std::cout << debug_string << std::endl;
  }
}
void debug_log(const std::string &debug_string, const int &debug_int,
               const bool &debug_flag) {
  if (debug_flag) {
    std::cout << debug_string << debug_int << std::endl;
  }
}

void err_log(const std::string &err, const bool &debug_flag) {
  if (debug_flag) {
    std::cerr << "ERROR: " << err << std::endl;
  }
}
void err_log(const std::string &err, const int &err_code,
             const bool &debug_flag) {
  if (debug_flag) {
    std::cerr << "ERROR: " << err << err_code << std::endl;
  }
}

} // namespace util_func