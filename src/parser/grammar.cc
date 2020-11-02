#include "../../include/parser/grammar.hh"

bool parser::grammar::isValidVariableName(std::string name) {
  return name.find(" ") == std::string::npos &&
         name.find(parser::tokens::escapeSequenceOperator) ==
             std::string::npos &&
         name.find(parser::tokens::lBrace) == std::string::npos &&
         name.find(parser::tokens::lBrackets) == std::string::npos &&
         name.find(parser::tokens::rBrace) == std::string::npos &&
         name.find(parser::tokens::rBrackets) == std::string::npos &&
         name.find(parser::tokens::varCallOperator) == std::string::npos;
}
