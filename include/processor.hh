#ifndef PROCESSOR_HH
#define PROCESSOR_HH

#include <iostream>
#include <list>

#include "parser/lexer.hh"
#include "utils/string.hh"
#include "variable.hh"

class processor {
  public:
  static bool processVariable(std::list<variable> *variables,
                              std::string statement);
};

#endif  // PROCESSOR_HH
