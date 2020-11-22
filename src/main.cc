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

void process(std::vector<std::string> lines);

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
void process(std::vector<std::string> lines) {
  std::vector<variable> variables;
  for (std::vector<std::string>::iterator it = lines.begin(); it < lines.end();
       ++it) {
    std::string line = parser::lexer::removeComments(*it);
    if (parser::lexer::isSkippableStatement(utils::string::trimStart(line)) ||
        processor::processVariable(&it, &lines, &variables) ||
        processor::processWorkflow(&it, &lines, &variables))
      continue;
    else if (parser::lexer::isWorkStatement(line)) {
      processor::skipWork(&it, &lines, &variables);
      continue;
    } else {
      std::cout << "What is this?" << std::endl
                << "Statement:" << line << std::endl;
      exit(1);
    }
  }
}
