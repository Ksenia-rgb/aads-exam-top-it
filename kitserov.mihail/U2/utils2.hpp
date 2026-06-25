#ifndef UTILS2_HPP
#define UTILS2_HPP

#include <cstddef>
#include <string>
#include "person.hpp"
namespace kitserov
{
  void skipSpaces(const std::string& str, size_t& pos) {
    const size_t len = str.size();
    while (pos < len && (str[pos] == ' ' || str[pos] == '\t')) {
      ++pos;
    }
  }
  bool parsePersonLine(const std::string& line, size_t& id, std::string& desc) {
    size_t pos = 0;
    const size_t len = line.size();

    skipSpaces(line, pos);
    if (pos == len) {
        return false;
    }

    id = 0;
    bool has_digit = false;
    while (pos < len && std::isdigit(static_cast< unsigned char >(line[pos]))) {
      has_digit = true;
      id = id * 10 + static_cast< size_t >(line[pos] - '0');
      ++pos;
    }
    if (!has_digit) {
      return false;
    }

    skipSpaces(line, pos);

    if (pos < len) {
      desc = line.substr(pos);
    } else {
      desc.clear();
    }

    if (desc.find_first_not_of(" \t") == std::string::npos) {
      return false;
    }
    return true;
  }
  bool parseUnsigned(const std::string& str, size_t& pos, size_t& value) {
    skipSpaces(str, pos);
    if (pos >= str.size()) {
      return false;
    }
    if (!std::isdigit(static_cast< unsigned char >(str[pos]))) {
      return false;
    }
    value = 0;
    while (pos < str.size() && std::isdigit(static_cast< unsigned char >(str[pos]))) {
      value = value * 10 + static_cast< size_t >(str[pos] - '0');
      ++pos;
    }
    return true;
  }
bool parseInt(const std::string& str, std::size_t& pos, int& value) {
    skipSpaces(str, pos);
    if (pos >= str.size()) {
        return false;
    }
    int sign = 1;
    if (str[pos] == '-') {
        sign = -1;
        ++pos;
    } else if (str[pos] == '+') {
        ++pos;
    }
    if (pos >= str.size() || !std::isdigit(static_cast<unsigned char>(str[pos]))) {
        return false;
    }
    long long val = 0;
    while (pos < str.size() && std::isdigit(static_cast<unsigned char>(str[pos]))) {
        val = val * 10 + (str[pos] - '0');
        ++pos;
    }
    val *= sign;
    // Проверка переполнения int (для простоты)
    if (val < static_cast<long long>(INT_MIN) || val > static_cast<long long>(INT_MAX)) {
        return false;
    }
    value = static_cast<int>(val);
    return true;
}

// Парсинг строки встречи вручную
bool parseMeetingLine(const std::string& line, std::size_t& id1, std::size_t& id2, int& dur) {
    std::size_t pos = 0;
    
    if (!parseUnsigned(line, pos, id1)) {
        return false;
    }
    
    if (!parseUnsigned(line, pos, id2)) {
        return false;
    }
    
    if (!parseInt(line, pos, dur)) {
        return false;
    }
    skipSpaces(line, pos);
    return pos == line.size();
  }
}

#endif
