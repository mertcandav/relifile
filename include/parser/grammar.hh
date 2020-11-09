#ifndef GRAMMAR_HH
#define GRAMMAR_HH

#include <iostream>

#include "lexer.hh"
#include "tokens.hh"

namespace parser {
class grammar {
  public:
  static bool isValidVariableName(std::string name);
};
}  // namespace parser

#endif  // GRAMMAR_HH
