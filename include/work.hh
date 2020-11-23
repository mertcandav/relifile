#ifndef WORK_HH
#define WORK_HH

#include <iostream>
#include <list>

/**
 * @typedef @struct work
 * @brief Work declarer
 * @field name Name of work
 * @field literals Commands of work
 */
typedef struct work {
  std::string name;
  std::vector<std::string> literals;
} work;

#endif  // WORK_HH
