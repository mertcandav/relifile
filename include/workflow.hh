#ifndef WORKFLOW_HH
#define WORKFLOW_HH

#include <iostream>
#include <list>

/**
 * @typedef @struct workflow
 * @field works Works of workflow
 */
typedef struct workflow {
  std::list<std::string> works;
} workflow;

#endif  // WORKFLOW_HH
