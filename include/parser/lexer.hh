#ifndef LEXER_HH
#define LEXER_HH

#include <iostream>
#include <list>
#include <vector>

#include "../processor.hh"
#include "../variable.hh"
#include "literal.hh"
#include "tokens.hh"

namespace parser {
class lexer {
  public:
  static std::string failProcess;

  static bool isSkippableStatement(std::string statement);
  static bool isVariableStatement(std::string statement);
  static bool isWorkflowStatement(std::string statement);
  static std::size_t findVariableLimit(std::string statement);
  static std::string removeComments(std::string statement);
  static std::vector<std::string> lexVariable(
      std::vector<std::string>::iterator* it, std::vector<std::string>* lines,
      std::vector<variable>* variables);
  static std::string getVariableNameFromStatement(std::string statement);
  static parser::literal getLiteral(std::vector<std::string>::iterator* it,
                                    std::vector<std::string>* lines,
                                    std::vector<variable>* variables);
  static std::string lexBraceRange(char open, char close,
                                   std::string statement);
};
}  // namespace parser

#endif  // LEXER_HH
