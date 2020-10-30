#include "../../include/parser/grammar.hh"

bool parser::grammar::isValidVariableName(std::string name) {
  return name.find(" ") == std::string::npos;
}
