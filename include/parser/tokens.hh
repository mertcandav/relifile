#ifndef TOKENS_HH
#define TOKENS_HH

#include <iostream>

namespace parser {
class tokens {
  public:
  static std::string INLINECOMMENT;
  static std::string ESCAPESEQUENCE;
  static std::string LPAR;
  static std::string RPAR;
  static std::string COLON;
  static std::string COMMA;
  static std::string SEMICOLON;
  static std::string PLUS;
  static std::string MINUS;
  static std::string STAR;
  static std::string SLASH;
  static std::string VBAR;
  static std::string AMPER;
  static std::string LESS;
  static std::string GREATER;
  static std::string EQUAL;
  static std::string NOTEQUAL;
  static std::string DOT;
  static std::string PERCENT;
  static std::string LBRACE;
  static std::string RBRACE;
  static std::string EQEQUAL;
  static std::string LESSEQUAL;
  static std::string GREATEREQUAL;
  static std::string TILDE;
  static std::string CIRCUMFLEX;
  static std::string LEFTSHIFT;
  static std::string RIGHTSHIFT;
  static std::string DOUBLESTAR;
  static std::string PLUSEQUAL;
  static std::string MINEQUAL;
  static std::string SLASHEQUAL;
  static std::string PERCENTEQUAL;
  static std::string AMPEREQUAL;
  static std::string VBAREQUAL;
  static std::string CIRCUMFLEXEQUAL;
  static std::string LEFTSHIFTEQUAL;
  static std::string RIGHTSHIFTEQUAL;
  static std::string DOUBLESTAREQUAL;
  static std::string DOUBLESLASHEQUAL;
  static std::string AT;
  static std::string ATEQUAL;
  static std::string LARROW;
  static std::string RARROW;
  static std::string ELLIPSIS;
  static std::string COLONEQUAL;
  static std::string DOLLAR;
  static std::string DOLLAREQUAL;

  static std::string workflowDefine;
  static std::string workDefine;
};
}  // namespace parser

#endif  // TOKENS_HH
