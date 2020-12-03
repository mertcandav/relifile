#include "../include/processor.hh"

bool processor::processVariable(std::vector<std::string>::iterator* it,
                                std::vector<std::string>* lines,
                                std::vector<variable>* variables) {
  if (!parser::lexer::isVariableStatement(**it))
    return false;
  variable var;
  std::vector<std::string> parts =
      parser::lexer::lexVariable(it, lines, variables);
  var.name = utils::string::trim(parts.front());
  if (!parser::grammar::isValidVariableName(var.name)) {
    std::cout << "Variable name is not valid!" << std::endl;
    exit(1);
  }
  std::vector<variable>::iterator iit = variables->begin();
  for (std::vector<variable>::iterator varit = variables->begin();
       varit < variables->end(); ++varit) {
    variable vvar = *varit;
    if (vvar.name == var.name) {
      var.value =
          utils::string::trim(processor::processValue(variables, parts.back()));
      variables->erase(iit);
      variables->insert(iit, var);
      return true;
    }
    ++it;
  }
  var.value =
      utils::string::trim(processor::processValue(variables, parts.back()));
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
  else if (value.substr(1, 1) == parser::tokens::VBAR)
    return parser::tokens::VBAR;
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
      sequence = utils::string::trim(sequence);
      index += sequence.length();
      for (std::vector<variable>::iterator it = variables->begin();
           it < variables->end(); ++it) {
        variable var = *it;
        if (var.name == sequence) {
          val += var.value;
          sequence = parser::lexer::failProcess;
          break;
        }
      }
      if (sequence != parser::lexer::failProcess) {
        std::cout << sequence << std::endl;
        std::cout << "Variable is cannot define!" << std::endl;
        exit(1);
      }
      continue;
    } else if (value[index] == parser::tokens::LPAR[0]) {
      std::string statement = parser::lexer::lexBraceRange(
          parser::tokens::LPAR[0], parser::tokens::RPAR[0],
          value.substr(index));
      val += processor::processValue(variables, statement);
      index += statement.length() + 1;
      continue;
    }
    val += value[index];
  }
  return val;
}

bool processor::processWorkflow(std::vector<std::string>::iterator* it,
                                std::vector<std::string>* lines,
                                std::vector<variable>* variables) {
  if (!parser::lexer::isWorkflowStatement(**it))
    return false;
  if (utils::string::trim(**it) != parser::tokens::workflowDefine) {
    std::cout << "Workflow define line is must are alone!" << std::endl;
    exit(1);
  }
  ++*it;
  workflow wf;
  for (; *it < lines->end(); ++*it) {
    std::string line =
        utils::string::trimStart(parser::lexer::removeComments(**it));
    if (line == "")
      break;
    else if (parser::lexer::isSkippableStatement(line))
      break;
    parser::literal lit = parser::lexer::getLiteral(it, lines, variables);
    wf.works.push_back(utils::string::trim(lit.value));
  }
  for (std::vector<std::string>::iterator workit = wf.works.begin();
       workit < wf.works.end(); ++workit) {
    std::vector<std::string> parts = utils::string::split(*workit, ' ');
    for (std::vector<std::string>::iterator partit = parts.begin();
         partit < parts.end(); ++partit) {
      if (*partit == "")
        continue;
      processor::processWork(*partit, it, lines, variables);
    }
  }
  return true;
}

bool processor::processWork(std::string name,
                            std::vector<std::string>::iterator* it,
                            std::vector<std::string>* lines,
                            std::vector<variable>* variables) {
  std::vector<std::string>::iterator wrkit =
      parser::lexer::findWork(name, *it, lines);
  work wrk = processor::skipWork(&wrkit, lines, variables);
  for (std::vector<std::string>::iterator i = wrk.literals.begin();
       i < wrk.literals.end(); ++i) {
    std::string lit = *i;
    std::cout << lit << std::endl;
    system((lit).c_str());
  }
  return true;
}

work processor::skipWork(std::vector<std::string>::iterator* it,
                         std::vector<std::string>* lines,
                         std::vector<variable>* variables) {
  if (!parser::lexer::isWorkStatement(utils::string::trim(**it))) {
    std::cout << "This statement is not work statement!" << std::endl;
    exit(1);
  }
  work wrk;
  wrk.name = parser::lexer::getWorkName(**it, false);
  size_t pos;
  if ((pos = wrk.name.find(' ')) != std::string::npos) {
    wrk.parameters = parser::lexer::lexParameters(wrk.name.substr(pos));
    wrk.name = wrk.name.substr(0, pos);
  }
  if (!parser::grammar::isValidVariableName(wrk.name)) {
    std::cout << "Work name is not valid!" << std::endl;
    exit(1);
  }
  for (std::vector<std::string>::iterator pit = wrk.parameters.begin();
       pit < wrk.parameters.end(); ++pit)
    *pit = processor::processValue(variables, *pit);
  ++*it;
  for (; *it < lines->end(); ++*it) {
    std::string line =
        utils::string::trimStart(parser::lexer::removeComments(**it));
    if (line == "")
      break;
    else if (parser::lexer::isSkippableStatement(line))
      break;
    wrk.literals.push_back(utils::string::trim(
        parser::lexer::getLiteral(it, lines, variables).value));
  }
  return wrk;
}
