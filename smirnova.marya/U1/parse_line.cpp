#include "parse_line.hpp"

#include <cctype>
#include <limits>

namespace smirnova
{
  bool parseLine(const std::string& line, size_t& id, std::string& info)
  {
    size_t pos = 0;
    id = 0;

    if (line.empty() ||
        !std::isdigit(static_cast< unsigned char >(line[pos])))
    {
      return false;
    }

    while (pos < line.size() &&
        std::isdigit(static_cast< unsigned char >(line[pos])))
    {
      size_t digit = line[pos] - '0';

      if (id > (std::numeric_limits< size_t >::max() - digit) / 10)
      {
        return false;
      }

      id = id * 10 + digit;
      ++pos;
    }

    if (pos == line.size() ||
        !std::isspace(static_cast< unsigned char >(line[pos])))
    {
      return false;
    }

    while (pos < line.size() &&
        std::isspace(static_cast< unsigned char >(line[pos])))
    {
      ++pos;
    }

    if (pos == line.size())
    {
      return false;
    }

    info = line.substr(pos);
    return true;
  }
}

