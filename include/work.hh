#ifndef WORK_HH
#define WORK_HH

#include <iostream>
#include <list>

/**
 * @typedef @struct work
 * @brief Work declarer
 * @field name Name of work
 * @field commands Commands of work
 */
typedef struct work {
  std::string name;
  std::list<std::string> commands;
} work;

#endif  // WORK_HH
