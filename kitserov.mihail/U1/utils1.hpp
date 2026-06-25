#ifndef UTILS1_HPP
#define UTILS1_HPP

#include <ostream>
#include <string>
#include <utility>
#include "person.hpp"
namespace kitserov
{
  void printAll(const PersonsContainer& container, std::ostream& out)
  {
    for (std::size_t i = 0; i < container.size_; ++i) {
      out << container.data_[i].id_ << ' ' << container.data_[i].info_ << '\n';
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
  template< class Stream, class File >
  std::pair< bool, int > chooseStream(Stream*& stream, File& file, bool& set, const std::string& arg, size_t substr)
  {
    if (set) {
      return {false, 1};
    }
    file.open(arg.substr(substr));
    if (!file.is_open()) {
      return {false, 2};
    }
    stream = &file;
    set = true;
    return {true, 0};
  }
}

#endif
