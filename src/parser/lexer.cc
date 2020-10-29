#include "../../include/parser/lexer.hh"

bool parser::lexer::isSkippableStatement(std::string statement) {
  return statement == "";
}

std::string parser::lexer::removeComments(std::string statement) {
  for (int index = 0; index < statement.length(); index++) {
    std::string ch = statement.substr(index, 1);
    if (ch != parser::tokens::inlineComment) {
      delete &ch;
      continue;
    }
    delete &ch;
    if (index == 0)
      return "";
    if (statement.substr(index - 1, 1) ==
        parser::tokens::escapeSequenceOperator)
      continue;
    return statement.substr(0, index);
  }
  return statement;
}
