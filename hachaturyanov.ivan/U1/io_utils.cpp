#include "io_utils.hpp"

#include <cctype>

namespace hachaturyanov
{
  List< std::string > split(std::string line)
  {
    List< std::string > result;
    std::string substr;
    bool has = false;
    for (size_t i = 0; i < line.size(); i++) {
      char c = line[i];
      if (c == ' ' || c == '\t' || c == '\n') {
        if (has) {
          result.addEnd(substr);
          substr.clear();
          has = false;
        }
      } else {
        substr.push_back(c);
        has = true;
      }
    }
    if (has) {
      result.addEnd(substr);
    }
    return result;
  }

  bool isdigit(std::string str)
  {
    if (str.size() == 0) {
      return false;
    }
    char c = ' ';
    bool digit = true;
    for (size_t i = 0; i < str.size(); i++) {
      c = str[i];
      if (!std::isdigit(c)) {
        digit = false;
      }
    }
    return digit;
  }

  std::pair< std::string, std::string > splitInTwo(std::string line)
  {
    std::pair< std::string, std::string > result;
    std::string substr;
    bool first = true;
    bool has = false;
    for (size_t i = 0; i < line.size(), i++) {
      char c = line[i];
      if (first) {
        if ((c == ' ' || c == '\t' || c == '\n') && has) {
          result.first = substr;
          substr.clear()
          first = false;
          has = false;
        } else {
          substr.push_back(c);
          has = true;
        }
      } else {
        substr.push_back(c);
      }
    }
    result.second = substr;
    return result;
  }
}
