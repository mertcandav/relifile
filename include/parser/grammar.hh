#ifndef GRAMMAR_HH
#define GRAMMAR_HH

#include <iostream>

namespace parser {
class grammar {
  public:
  static bool isValidVariableName(std::string name);
};
}  // namespace parser

#endif  // GRAMMAR_HH
