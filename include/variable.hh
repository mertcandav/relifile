#ifndef VARIABLE_HH
#define VARIABLE_HH

#include <iostream>

/**
 * @typedef @struct variable
 * @field name Name of variable
 * @field value Value of variable
 */
typedef struct variable {
  std::string name;
  std::string value;
} variable;

#endif  // VARIABLE_HH
