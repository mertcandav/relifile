#include "../include/processor.hh"

bool processor::processVariable(std::list<variable> *variables,
                                std::string statement) {
  if (!parser::lexer::isVariableStatement(statement))
    return false;
  variable var;
  std::list<std::string> parts = parser::lexer::lexVariable(statement);
  var.name = utils::string::trim(parts.front());
  var.value = parts.back();
  delete &parts;
  variables->push_back(var);
  return true;
}
