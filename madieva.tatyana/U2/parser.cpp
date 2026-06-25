#include "parser.hpp"
#include <cctype>

namespace madieva {

  bool parsePersonLine(const std::string & line, Person & person) {
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

  bool parseMeetLine(const std::string & line, Meet & meet) {
    meet.person1_id_ = 0;
    meet.person2_id_ = 0;
    meet.duration_ = 0;

    if (line.empty()) {
      return false;
    }

    std::size_t pos = 0;
    while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos]))) {
      unsigned char c = static_cast< unsigned char >(line[pos]);
      if (!std::isdigit(c)) {
        return false;
      }
      meet.person1_id_ = meet.person1_id_ * 10 + (c - '0');
      ++pos;
    }

    if (pos == 0 || pos == line.size()) {
      return false;
    }

    while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos]))) {
      ++pos;
    }

    if (pos == line.size()) {
      return false;
    }

    std::size_t id2_start = pos;
    while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos]))) {
      unsigned char c = static_cast< unsigned char >(line[pos]);
      if (!std::isdigit(c)) {
        return false;
      }
      meet.person2_id_ = meet.person2_id_ * 10 + (c - '0');
      ++pos;
    }

    if (pos == id2_start || pos == line.size()) {
      return false;
    }

    while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos]))) {
      ++pos;
    }

    if (pos == line.size()) {
      return false;
    }

    std::size_t dur_start = pos;
    while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos]))) {
      unsigned char c = static_cast< unsigned char >(line[pos]);
      if (!std::isdigit(c)) {
        return false;
      }
      meet.duration_ = meet.duration_ * 10 + (c - '0');
      ++pos;
    }

    if (pos == dur_start) {
      return false;
    }

    while (pos < line.size()) {
      if (!std::isspace(static_cast< unsigned char >(line[pos]))) {
        return false;
      }
      ++pos;
    }

    return true;
  }

}
