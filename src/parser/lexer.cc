#include "../../include/parser/lexer.hh"

std::string parser::lexer::failProcess = "_ERROR_";

bool parser::lexer::isSkippableStatement(std::string statement) {
  return statement == "";
}

bool parser::lexer::isVariableStatement(std::string statement) {
  return statement.substr(0, 1) == parser::tokens::varCallOperator;
}

bool parser::lexer::isWorkflowStatement(std::string statement) {
  return statement.substr(0, parser::tokens::workflowDefine.length()) ==
         parser::tokens::workflowDefine;
}

std::string parser::lexer::removeComments(std::string statement) {
  for (int index = 0; index < statement.length(); ++index) {
    std::string ch = statement.substr(index, 1);
    if (processor::processSequence(statement.substr(index)) != failProcess) {
      delete &ch;
      ++index;
      continue;
    }
    if (ch != parser::tokens::inlineComment) {
      delete &ch;
      continue;
    }
    delete &ch;
    if (index == 0)
      return "";
    return statement.substr(0, index);
  }
  return statement;
}

std::list<std::string> parser::lexer::lexVariable(std::string statement) {
  std::list<std::string> parts;
  std::size_t index = statement.find(parser::tokens::varDefOperator);
  parts.push_back(index != std::string::npos ? statement.substr(1, index - 1)
                                             : statement.substr(1));
  parts.push_back(index != std::string::npos ? statement.substr(index + 1)
                                             : "");
  return parts;
}

std::string parser::lexer::getVariableNameFromStatement(std::string statement) {
  if (statement.substr(0, 1) != parser::tokens::varCallOperator)
    return lexer::failProcess;
  std::size_t index = statement.find(" ");
  std::string name = index != std::string::npos ? statement.substr(1, index - 1)
                                                : statement.substr(1);
  index = name.find(parser::tokens::varCallOperator);
  return index != std::string::npos ? name.substr(0, index) : name;
}
