#include "Parse.hpp"

#include <cctype>

namespace yalovsky
{
  void skipSpaces(const std::string& line, size_t& pos)
  {
    while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
    {
      ++pos;
    }
  }

  bool atEnd(const std::string& line, size_t pos)
  {
    skipSpaces(line, pos);
    return pos == line.size();
  }

  bool readNumber(const std::string& line, size_t& pos, size_t& value)
  {
    skipSpaces(line, pos);
    const size_t start = pos;
    const size_t decimalBase = 10;
    size_t result = 0;
    while (pos < line.size() && std::isdigit(static_cast< unsigned char >(line[pos])))
    {
      const size_t digit = static_cast< size_t >(line[pos] - '0');
      result = result * decimalBase + digit;
      ++pos;
    }
    if (pos == start)
    {
      return false;
    }
    value = result;
    return true;
  }

  bool readWord(const std::string& line, size_t& pos, std::string& word)
  {
    skipSpaces(line, pos);
    const size_t start = pos;
    while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos])))
    {
      ++pos;
    }
    if (pos == start)
    {
      return false;
    }
    word = line.substr(start, pos - start);
    return true;
  }

  bool readQuoted(const std::string& line, size_t& pos, std::string& value)
  {
    skipSpaces(line, pos);
    if (pos == line.size() || line[pos] != '"')
    {
      return false;
    }
    ++pos;
    const size_t start = pos;
    while (pos < line.size() && line[pos] != '"')
    {
      ++pos;
    }
    if (pos == line.size())
    {
      return false;
    }
    value = line.substr(start, pos - start);
    ++pos;
    return true;
  }
}
