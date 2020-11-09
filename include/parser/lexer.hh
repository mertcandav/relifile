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
  static std::vector<std::string> lexVariable(std::string statement);
  static std::string getVariableNameFromStatement(std::string statement);
  static parser::literal getLiteral(int index, std::vector<std::string>* lines,
                                    std::vector<variable>* variables);
};
}  // namespace parser

#endif  // LEXER_HH
