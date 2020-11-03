#ifndef LEXER_HH
#define LEXER_HH

#include <iostream>
#include <list>

#include "../processor.hh"
#include "tokens.hh"

namespace parser {
class lexer {
  public:
  static std::string failProcess;

  static bool isSkippableStatement(std::string statement);
  static bool isVariableStatement(std::string statement);
  static std::string removeComments(std::string statement);
  static std::list<std::string> lexVariable(std::string statement);
  static std::string getVariableNameFromStatement(std::string statement);
};
}  // namespace parser

#endif  // LEXER_HH
