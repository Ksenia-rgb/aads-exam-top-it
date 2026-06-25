#include "io.hpp"
#include <string>

static void stripCr(std::string& line)
{
  if (!line.empty() && line.back() == '\r') {
    line.pop_back();
  }
}

static bool hasId(const gordejchik::dynarray_t< gordejchik::person_t >& arr, size_t id)
{
  for (size_t i = 0; i < arr.size_; ++i) {
    if (arr.data_[i].id_ == id) {
      return true;
    }
  }
  return false;
}

static bool parseLine(const std::string& line, size_t& id, std::string& info)
{
  if (line.empty()) {
    return false;
  }
  size_t pos = 0;
  try {
    unsigned long long raw = std::stoull(line, &pos);
    id = static_cast< size_t >(raw);
  } catch (...) {
    return false;
  }
  if (pos == line.size()) {
    return false;
  }
  if (line[pos] != ' ' && line[pos] != '\t') {
    return false;
  }
  size_t descStart = pos;
  while (descStart < line.size() && (line[descStart] == ' ' || line[descStart] == '\t')) {
    ++descStart;
  }
  if (descStart == line.size()) {
    return false;
  }
  info = line.substr(descStart);
  return true;
}
