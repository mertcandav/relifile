#ifndef LITERAL_HH
#define LITERAL_HH

#include <iostream>

namespace parser {
/**
 * @typedef @struct literal
 * @brief A literal declare
 * @field value Value of literal
 * @field line Lines count of literal
 */
typedef struct literal {
  std::string value;
  int line;
} literal;
}  // namespace parser

#endif  // LITERAL_HH
