#include "../../include/parser/grammar.hh"

bool parser::grammar::isValidVariableName(std::string name) {
  return parser::lexer::findVariableLimit(name) == std::string::npos;
}
