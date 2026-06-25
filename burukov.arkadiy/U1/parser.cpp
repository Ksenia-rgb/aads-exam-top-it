#include "parser.hpp"

#include <cstddef>
#include <string>

#include "person.hpp"

namespace burukov
{

  ParseResult parseLine(const std::string& line, Person& out)
  {
    size_t pos = line.find_first_not_of(" \t");
    if (pos == std::string::npos)
    {
      return PARSE_BLANK;
    }
    size_t id = 0;
    bool hasDigit = false;
    while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9')
    {
      id = id * 10 + static_cast< size_t >(line[pos] - '0');
      hasDigit = true;
      ++pos;
    }
    if (!hasDigit)
    {
      return PARSE_INVALID;
    }
    size_t start = line.find_first_not_of(" \t", pos);
    if (start == std::string::npos || start == pos)
    {
      return PARSE_INVALID;
    }
    out.id = id;
    out.info = line.substr(start);
    return PARSE_OK;
  }

}
