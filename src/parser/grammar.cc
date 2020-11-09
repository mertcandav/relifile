#include "../../include/parser/grammar.hh"

bool parser::grammar::isValidVariableName(std::string name) {
  return name.find(" ") == std::string::npos &&
         name.find(parser::tokens::ESCAPESEQUENCE) == std::string::npos &&
         name.find(parser::tokens::LPAR) == std::string::npos &&
         name.find(parser::tokens::LPAR) == std::string::npos &&
         name.find(parser::tokens::DOLLAR) == std::string::npos &&
         name.find(parser::tokens::SLASH) == std::string::npos &&
         name.find(parser::tokens::COMMA) == std::string::npos &&
         name.find(parser::tokens::AT) == std::string::npos &&
         name.find(parser::tokens::AMPER) == std::string::npos &&
         name.find(parser::tokens::SEMICOLON) == std::string::npos &&
         name.find(parser::tokens::TILDE) == std::string::npos &&
         name.find(parser::tokens::STAR) == std::string::npos &&
         name.find(parser::tokens::PERCENT) == std::string::npos &&
         name.find(parser::tokens::EQUAL) == std::string::npos &&
         name.find(parser::tokens::PLUS) == std::string::npos &&
         name.find(parser::tokens::MINUS) == std::string::npos &&
         name.find(parser::tokens::VBAR) == std::string::npos &&
         name.find(parser::tokens::GREATER) == std::string::npos &&
         name.find(parser::tokens::LESS) == std::string::npos &&
         name.find(parser::tokens::COLON) == std::string::npos &&
         name.find(parser::tokens::CIRCUMFLEX) == std::string::npos;
}
