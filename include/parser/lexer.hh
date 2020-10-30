#ifndef LEXER_HH
#define LEXER_HH

#include <iostream>
#include <list>

#include "tokens.hh"

namespace parser {
class lexer {
  public:
  static bool isSkippableStatement(std::string statement);
  static bool isVariableStatement(std::string statement);
  static std::string removeComments(std::string statement);
  static std::list<std::string> lexVariable(std::string statement);
};
}  // namespace parser

#endif  // LEXER_HH
