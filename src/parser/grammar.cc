#include "../../include/parser/grammar.hh"

bool parser::grammar::isValidVariableName(std::string name) {
  return name.find(" ") == std::string::npos &&
         name.find(parser::tokens::ESCAPESEQUENCE) == std::string::npos &&
         name.find(parser::tokens::LPAR) == std::string::npos &&
         name.find(parser::tokens::LPAR) == std::string::npos &&
         name.find(parser::tokens::DOLLAR) == std::string::npos;
}
