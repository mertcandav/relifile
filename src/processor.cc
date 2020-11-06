#include "../include/processor.hh"

bool processor::processVariable(std::vector<variable>* variables,
                                std::string statement) {
  if (!parser::lexer::isVariableStatement(statement))
    return false;
  variable var;
  std::vector<std::string> parts = parser::lexer::lexVariable(statement);
  var.name = utils::string::trim(parts.front());
  if (!parser::grammar::isValidVariableName(var.name)) {
    std::cout << "Variable name is not valid!" << std::endl;
    exit(1);
  }
  std::vector<variable>::iterator it = variables->begin();
  for (variable vvar : *variables) {
    if (vvar.name == var.name) {
      var.value = processValue(variables, parts.back());
      variables->erase(it);
      variables->insert(it, var);
      return true;
    }
    ++it;
  }
  var.value = processValue(variables, parts.back());
  variables->push_back(var);
  return true;
}

std::string processor::processSequence(std::string value) {
  if (value.substr(0, 1) != parser::tokens::ESCAPESEQUENCE)
    return parser::lexer::failProcess;

  if (value.substr(1, 1) == " ") {
    std::cout << "Escape sequence is cannot use alone!" << std::endl;
    exit(1);
  } else if (value.substr(1, 1) == parser::tokens::ESCAPESEQUENCE)
    return parser::tokens::ESCAPESEQUENCE;
  else if (value.substr(1, 1) == parser::tokens::INLINECOMMENT)
    return parser::tokens::INLINECOMMENT;
  else if (value.substr(1, 1) == parser::tokens::DOLLAR)
    return parser::tokens::DOLLAR;
  else
    return parser::lexer::failProcess;
}

std::string processor::processValue(std::vector<variable>* variables,
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

int processor::processWorkflow(int index, std::vector<std::string>* lines,
                               std::vector<variable>* variables,
                               std::vector<workflow>* workflows) {
  int iindex = -1;
  for (std::string line : *lines) {
    ++iindex;
    if (iindex < index)
      continue;
    if (iindex == index) {
      if (utils::string::trim(line) != parser::tokens::workflowDefine) {
        std::cout << "Workflow define line is must are alone!" << std::endl;
        exit(1);
      }
      continue;
    }
    if (utils::string::trimStart(line) == "")
      break;
    line = parser::lexer::removeComments(line);
    if (parser::lexer::isSkippableStatement(utils::string::trimStart(line)))
      continue;
    workflow wf;
    wf.works.push_back(
        utils::string::trim(processor::processValue(variables, line)));
    workflows->push_back(wf);
  }
  return iindex - index;
}
