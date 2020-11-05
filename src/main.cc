// Copyright (c) 2020 Mertcan Davulcu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>

#include "../include/parser/lexer.hh"
#include "../include/processor.hh"
#include "../include/utils/io.hh"
#include "../include/variable.hh"
#include "../include/work.hh"

void process(std::list<std::string> lines);

/**
 * @fn main
 * @brief Entry point
 * @param argc Count of arguments
 * @param argv Arguments
 * @return Exit code
 */
int main(int argc, char const* argv[]) {
  if (!utils::io::existFile("./relifile")) {
    std::cout << "Relifile is not found!" << std::endl;
    return 1;
  }
  process(utils::io::getLinesOfFile("./relifile"));
  return 0;
}

/**
 * @fn process
 * @brief Process relifile
 * @param lines Lines of file
 * @return N/A
 */
void process(std::list<std::string> lines) {
  std::list<variable> variables;
  std::list<workflow> workflows;
  int index = -1, skipping = 0;
  for (std::string line : lines) {
    ++index;
    if (skipping > 0) {
      --skipping;
      continue;
    }
    line = parser::lexer::removeComments(line);
    if (parser::lexer::isSkippableStatement(utils::string::trimStart(line)))
      continue;

    if (processor::processVariable(&variables, line))
      continue;
    else if (parser::lexer::isWorkflowStatement(line)) {
      skipping +=
          processor::processWorkflow(index, &lines, &variables, &workflows);
      continue;
    } else {
      std::cout << "What is this?" << std::endl
                << "Statement:" << line << std::endl;
      exit(1);
    }
  }
}
