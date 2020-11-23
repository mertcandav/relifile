#ifndef STRING_HH
#define STRING_HH

#include <iostream>

namespace utils {
class string {
  public:
  static std::string trimStart(std::string value);
  static std::string trimEnd(std::string value);
  static std::string trim(std::string value);
};
}  // namespace utils

#endif  // STRING_HH
