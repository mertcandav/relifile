#ifndef IO_HH
#define IO_HH

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif  // _WIN32

namespace utils {
class io {
  public:
  /** @brief Working directory */
  static char* _WORKING_DIR_;

  static bool existFile(std::string path);
  static std::vector<std::string> getLinesOfFile(std::string path);
};
}  // namespace utils

#endif  // IO_HH
