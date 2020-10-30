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
  var.value = parts.back();
  delete &parts;
  variables->push_back(var);
  return true;
}
