#include "../../include/utils/string.hh"

std::string utils::string::trimStart(std::string value) {
  for (int index = 0; index < value.length(); ++index)
    if (value[index] != ' ')
      return value.substr(index);
  return value;
}

std::string utils::string::trimEnd(std::string value) {
  for (int index = value.length() - 1; index >= 0; --index)
    if (value[index] != ' ')
      return value.substr(0, index + 1);
  return value;
}

std::string utils::string::trim(std::string value) {
  return trimEnd(trimStart(value));
}
