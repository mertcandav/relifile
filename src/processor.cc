#include "../include/processor.hh"

bool processor::processVariable(std::list<variable>* variables,
                                std::string statement) {
  if (!parser::lexer::isVariableStatement(statement))
    return false;
  variable var;
  std::list<std::string> parts = parser::lexer::lexVariable(statement);
  var.name = utils::string::trim(parts.front());
  if (!parser::grammar::isValidVariableName(var.name)) {
    std::cout << "Variable name is not valid!" << std::endl;
    exit(1);
  }
  var.value = processValue(variables, parts.back());
  delete &parts;
  variables->push_back(var);
  return true;
}

std::string processor::processSequence(std::string value) {
  if (value.substr(0, 1) != parser::tokens::escapeSequenceOperator)
    return parser::lexer::failProcess;

  if (value.substr(1, 1) == " ") {
    std::cout << "Escape sequence is cannot use alone!" << std::endl;
    exit(1);
  } else if (value.substr(1, 1) == parser::tokens::escapeSequenceOperator)
    return parser::tokens::escapeSequenceOperator;
  else if (value.substr(1, 1) == parser::tokens::inlineComment)
    return parser::tokens::inlineComment;
  else if (value.substr(1, 1) == parser::tokens::varCallOperator)
    return parser::tokens::varCallOperator;
  else
    return parser::lexer::failProcess;
}

std::string processor::processValue(std::list<variable>* variables,
                                    std::string value) {
  std::string val;
  for (int index = 0; index < value.length(); ++index) {
    std::string sequence = processSequence(value.substr(index));
    if (sequence != parser::lexer::failProcess) {
      val += sequence;
      ++index;
      continue;
    }
    sequence = parser::lexer::getVariableNameFromStatement(value.substr(index));
    if (sequence != parser::lexer::failProcess) {
      index += sequence.length();
      for (variable var : *variables)
        if (var.name == sequence) {
          val += var.value;
          sequence = parser::lexer::failProcess;
          break;
        }
      if (sequence != parser::lexer::failProcess) {
        std::cout << "Variable is cannot define!" << std::endl;
        exit(1);
      }
      continue;
    }
    val += value[index];
  }
  return val;
}
