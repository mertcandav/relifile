#ifndef PROCESSOR_HH
#define PROCESSOR_HH

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "parser/grammar.hh"
#include "parser/lexer.hh"
#include "parser/literal.hh"
#include "utils/string.hh"
#include "variable.hh"
#include "workflow.hh"

class processor {
  public:
  static bool processVariable(std::vector<variable>* variables,
                              std::string statement);
  static std::string processSequence(std::string value);
  static std::string processValue(std::vector<variable>* variables,
                                  std::string value);
  static bool processWorkflow(std::vector<std::string>::iterator* it,
                              std::vector<std::string>* lines,
                              std::vector<variable>* variables,
                              std::vector<workflow>* workflows);
};

#endif  // PROCESSOR_HH
