#ifndef UTILS1_HPP
#define UTILS1_HPP

#include <ostream>
#include <person.hpp>
#include <string>
namespace kitserov
{
  void printAll(const PersonsContainer& container, std::ostream& out)
  {
    for (std::size_t i = 0; i < container.size; ++i) {
      out << container.data[i].id << ' ' << container.data[i].info << '\n';
    }
  }
  bool readLine(const std::string& line, size_t& id, std::string& info)
  {
    size_t pos = 0;
    const size_t len = line.size();
    while (pos < len && line[pos] == ' ') {
      ++pos;
    }
    if (pos == len) {
      return false;
    }
    id = 0;
    bool hasDigit = false;
    while (pos < len && std::isdigit(static_cast< unsigned char >(line[pos]))) {
      hasDigit = true;
      id = id * 10 + static_cast< size_t >(line[pos] - '0');
      ++pos;
    }
    if (!hasDigit) {
      return false;
    }
    while (pos < len && line[pos] == ' ') {
      ++pos;
    }
    if (pos < len) {
      info = line.substr(pos);
    } else {
      info.clear();
    }
    return true;
  }
}

#endif