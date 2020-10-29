#ifndef TOKENS_HH
#define TOKENS_HH

#include <iostream>

namespace parser {
class tokens {
  public:
  static std::string inlineComment;
  static std::string lBrace;
  static std::string rBrace;
  static std::string lBrackets;
  static std::string rBrackets;
  static std::string varDefOperator;
  static std::string varConcatOperator;
  static std::string varCallOperator;
  static std::string workflowDefine;
  static std::string workDefine;
  static std::string escapeSequenceOperator;
};
}  // namespace parser

#endif  // TOKENS_HH
