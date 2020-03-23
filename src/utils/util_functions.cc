#include "include/util_functions.h"

namespace UtilFunc {

template <typename T> std::string custom_to_string(const T &value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}

void debug_log(const std::string &debug_string, const bool &debug_flag) {
  if (debug_flag) {
    std::cout << debug_string << "\n";
  }
}
void debug_log(const std::string &debug_string, const int &debug_int,
               const bool &debug_flag) {
  if (debug_flag) {
    std::cout << debug_string << debug_int << "\n";
  }
}

} // namespace UtilFunc