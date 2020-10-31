#ifndef PROCESSOR_HH
#define PROCESSOR_HH

#include <iostream>
#include <list>

#include "parser/grammar.hh"
#include "parser/lexer.hh"
#include "utils/string.hh"
#include "variable.hh"

class processor {
  public:
  static bool processVariable(std::list<variable>* variables,
                              std::string statement);
  static std::string processSequence(std::string value);
};

#endif  // PROCESSOR_HH
