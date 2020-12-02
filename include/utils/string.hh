#ifndef STRING_HH
#define STRING_HH

#include <iostream>
#include <list>
#include <vector>

namespace utils {
class string {
  public:
  static std::string trimStart(std::string value);
  static std::string trimEnd(std::string value);
  static std::string trim(std::string value);
  static std::vector<std::string> split(std::string value, char seperator);
};
}  // namespace utils

#endif  // STRING_HH
