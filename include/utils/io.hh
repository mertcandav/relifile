#ifndef IO_HH
#define IO_HH

#include <stdio.h>

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
};
}  // namespace utils

#endif  // IO_HH
