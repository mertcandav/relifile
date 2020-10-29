#include "../../include/utils/io.hh"

char* utils::io::_WORKING_DIR_ = getcwd(NULL, 0);

bool utils::io::existFile(std::string path) {
  std::ifstream file(path);
  bool state = file.good();
  delete &file;
  return state;
}

std::list<std::string> utils::io::getLinesOfFile(std::string path) {
  std::ifstream file(path);
  if (!file.good()) {
    /* write exit processes in here at after time */
  }
  std::list<std::string> lines;
  std::string line;
  while (std::getline(file, line)) lines.push_back(line);
  delete &file;
  return lines;
}
