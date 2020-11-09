#include "../../include/parser/lexer.hh"

std::string parser::lexer::failProcess = "_ERROR_";

bool parser::lexer::isSkippableStatement(std::string statement) {
  return statement == "";
}

bool parser::lexer::isVariableStatement(std::string statement) {
  return statement.substr(0, 1) == parser::tokens::DOLLAR;
}

bool parser::lexer::isWorkflowStatement(std::string statement) {
  return statement.substr(0, parser::tokens::workflowDefine.length()) ==
         parser::tokens::workflowDefine;
}

std::size_t parser::lexer::findVariableLimit(std::string statement) {
  std::size_t res = statement.find(" ");
  res = res == std::string::npos
            ? statement.find(parser::tokens::ESCAPESEQUENCE)
            : res;
  res = res == std::string::npos ? statement.find(parser::tokens::LPAR) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::LPAR) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::DOLLAR) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::SLASH) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::COMMA) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::AT) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::AMPER) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::SEMICOLON)
                                 : res;
  res = res == std::string::npos ? statement.find(parser::tokens::TILDE) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::STAR) : res;
  res =
      res == std::string::npos ? statement.find(parser::tokens::PERCENT) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::EQUAL) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::PLUS) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::MINUS) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::VBAR) : res;
  res =
      res == std::string::npos ? statement.find(parser::tokens::GREATER) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::LESS) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::COLON) : res;
  res = res == std::string::npos ? statement.find(parser::tokens::CIRCUMFLEX)
                                 : res;
  return res;
}

std::string parser::lexer::removeComments(std::string statement) {
  for (int index = 0; index < statement.length(); ++index) {
    std::string ch = statement.substr(index, 1);
    if (processor::processSequence(statement.substr(index)) != failProcess) {
      ++index;
      continue;
    }
    if (ch != parser::tokens::INLINECOMMENT)
      continue;
    if (index == 0)
      return "";
    return statement.substr(0, index);
  }
  return statement;
}

std::vector<std::string> parser::lexer::lexVariable(std::string statement) {
  std::vector<std::string> parts;
  std::size_t index = statement.find(parser::tokens::EQUAL);
  parts.push_back(index != std::string::npos ? statement.substr(1, index - 1)
                                             : statement.substr(1));
  parts.push_back(index != std::string::npos ? statement.substr(index + 1)
                                             : "");
  return parts;
}

std::string parser::lexer::getVariableNameFromStatement(std::string statement) {
  if (statement.substr(0, 1) != parser::tokens::DOLLAR)
    return lexer::failProcess;
  std::size_t pos = parser::lexer::findVariableLimit(statement.substr(1));
  return pos != std::string::npos ? statement.substr(1, pos)
                                  : statement.substr(1);
}

parser::literal parser::lexer::getLiteral(int index,
                                          std::vector<std::string>* lines,
                                          std::vector<variable>* variables) {
  literal lit;
  lit.line = 0;
  int iindex = -1;
  for (std::string line : *lines) {
    ++iindex;
    if (iindex < index)
      continue;
    line = utils::string::trimStart(parser::lexer::removeComments(line));
    if (line == "" ||
        (iindex != index && line.substr(0, 1) == parser::tokens::VBAR))
      break;
    else if (parser::lexer::isSkippableStatement(line))
      break;
    ++lit.line;
    if (iindex == index) {
      if (line.substr(0, 1) != parser::tokens::VBAR) {
        std::cout << "Literal origin not defined!" << std::endl;
        exit(1);
      }
      lit.value += processor::processValue(variables, line.substr(1));
      continue;
    }
    lit.value += processor::processValue(variables, line);
  }
  return lit;
}
