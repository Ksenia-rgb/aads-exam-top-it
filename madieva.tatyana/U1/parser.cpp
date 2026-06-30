#include "parser.hpp"
#include <cctype>

bool madieva::parseLine(const std::string& line, Person& person) {
  person.id_ = 0;
  person.info_.clear();

  if (line.empty()) {
    return false;
  }

  if (std::isspace(static_cast< unsigned char >(line[0]))) {
    return false;
  }

  std::size_t pos = 0;
  while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos]))) {
    unsigned char c = static_cast< unsigned char >(line[pos]);
    if (!std::isdigit(c)) {
      return false;
    }
    ++pos;
  }

  if (pos == 0 || pos == line.size()) {
    return false;
  }

  for (std::size_t i = 0; i < pos; ++i) {
    person.id_ = person.id_ * 10 + (static_cast< unsigned char >(line[i]) - '0');
  }

  std::size_t info_start = pos;
  while (info_start < line.size() && std::isspace(static_cast< unsigned char >(line[info_start]))) {
    ++info_start;
  }

  if (info_start == line.size()) {
    return false;
  }

  person.info_ = line.substr(info_start);
  return !person.info_.empty();
}
