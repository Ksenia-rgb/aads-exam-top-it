#include "parser.hpp"

bool madieva::parseLine(const std::string & line, Person & person) {
  if (line.empty()) {
    return false;
  }

  size_t pos = 0;
  while (pos < line.size() && line[pos] != ' ') {
    ++pos;
  }
  if (pos == line.size()) {
    return false;
  }

  person.id_ = 0;
  for (size_t i = 0; i < pos; ++i) {
    unsigned char c = static_cast< unsigned char >(line[i]);
    if (!std::isdigit(c)) {
      return false;
    }
    person.id_ = person.id_ * 10 + (c - '0');
  }
  size_t info_start = pos;
  while (info_start < line.size() && line[info_start] == ' ') {
    ++info_start;
  }
  if (info_start == line.size()) {
    return false;
  }
  person.info_ = line.substr(info_start);
  return !person.info_.empty();
}