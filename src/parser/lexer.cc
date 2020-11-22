#include "../../include/parser/lexer.hh"

std::string parser::lexer::failProcess = "_ERROR_";

bool parser::lexer::isSkippableStatement(std::string statement) {
  return statement == "";
}

bool parser::lexer::isVariableStatement(std::string statement) {
  return statement.substr(0, 1) == parser::tokens::DOLLAR;
}

bool parser::lexer::isWorkflowStatement(std::string statement) {
  return statement == parser::tokens::workflowDefine;
}

bool parser::lexer::isWorkStatement(std::string statement) {
  return statement.substr(0, parser::tokens::workDefine.length() + 1) ==
         parser::tokens::workDefine + " ";
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

std::vector<std::string> parser::lexer::lexVariable(
    std::vector<std::string>::iterator* it, std::vector<std::string>* lines,
    std::vector<variable>* variables) {
  std::vector<std::string> parts;
  std::size_t index = (**it).find(parser::tokens::EQUAL);
  parts.push_back(index != std::string::npos ? (**it).substr(1, index - 1)
                                             : (**it).substr(1));
  if (index != std::string::npos) {
    parts.push_back((**it).substr(index + 1));
    **+it;
    return parts;
  }
  ++*it;
  std::string val = "";
  for (; *it < lines->end(); ++*it) {
    std::string line = parser::lexer::removeComments(**it);
    if (utils::string::trimStart(line) == "")
      break;
    else if (parser::lexer::isSkippableStatement(line))
      break;
    val += line;
  }
  parts.push_back(val);
  return parts;
}

std::string parser::lexer::getVariableNameFromStatement(std::string statement) {
  if (statement.substr(0, 1) != parser::tokens::DOLLAR)
    return lexer::failProcess;
  std::size_t pos = parser::lexer::findVariableLimit(statement.substr(1));
  return pos != std::string::npos ? statement.substr(1, pos)
                                  : statement.substr(1);
}

parser::literal parser::lexer::getLiteral(
    std::vector<std::string>::iterator* it, std::vector<std::string>* lines,
    std::vector<variable>* variables) {
  literal lit;
  lit.line = 0;
  if ((**it).substr(0, 1) != parser::tokens::VBAR) {
    std::cout << "Literal origin not defined!" << std::endl;
    exit(1);
  }
  lit.value += processor::processValue(variables, (**it).substr(1));
  ++*it;
  for (; *it < lines->end(); ++*it) {
    std::string line =
        utils::string::trimStart(parser::lexer::removeComments(**it));
    if (line == "") {
      --*it;
      break;
    } else if (parser::lexer::isSkippableStatement(line)) {
      --*it;
      break;
    }
    ++lit.line;
    lit.value += processor::processValue(variables, line);
  }
  return lit;
}

std::string parser::lexer::lexBraceRange(char open, char close,
                                         std::string statement) {
  int count = 0;
  for (char ch : statement) {
    if (ch == open)
      ++count;
    else if (ch == close)
      --count;
  }
  if (count > 0) {
    std::cout << "Bracket is opened but not closed!" << std::endl;
    exit(1);
  } else if (count < 0) {
    std::cout << "Bracket is not opened but closed!" << std::endl;
    exit(1);
  }
  if (statement[0] == open)
    return statement.substr(1, statement.length() - 2);
  return statement;
}

std::vector<std::string>::iterator parser::lexer::findWork(
    std::string name, std::vector<std::string>::iterator it,
    std::vector<std::string>* lines) {
  for (; it < lines->end(); ++it) {
    std::string line = utils::string::trim(*it);
    if (!lexer::isWorkStatement(line))
      continue;
    if (parser::lexer::getWorkName(line) == name)
      return it;
  }
  std::cout << "Work is cannot define!" << std::endl;
  exit(1);
}

std::string parser::lexer::getWorkName(std::string statement) {
  return utils::string::trim(utils::string::trim(statement).substr(
      parser::tokens::workDefine.length()));
}
