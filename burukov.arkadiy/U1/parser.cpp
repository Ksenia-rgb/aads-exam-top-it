#include "parser.hpp"
#include <cstddef>
#include <string>
#include "person.hpp"

namespace burukov
{

  bool parseLine(const std::string& line, Person& out)
  {
    size_t pos = line.find_first_not_of(" \t");
    if (pos == std::string::npos)
    {
      return false;
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
      return false;
    }
    size_t start = line.find_first_not_of(" \t", pos);
    if (start == std::string::npos || start == pos)
    {
      return false;
    }
    out.id = id;
    out.info = line.substr(start);
    return true;
  }

}
