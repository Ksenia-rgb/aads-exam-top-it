#include "parse.hpp"
#include "io.hpp"

#include <string>
#include <iostream>

namespace ulanova
{
  ParseResult readPersons(std::istream & in)
  {
    Array< Person > arr = mArray< Person >();
    size_t ignoredCount = 0;
    std::string line;
    while (std::getline(in, line))
    {
      size_t id = 0;
      size_t pos = 0;
      bool valid = false;
      while (pos < line.size() && line[pos] == ' ')
      {
        ++pos;
      }
      while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9')
      {
        id = id * 10 + (line[pos] - '0');
        ++pos;
        valid = true;
      }
      if (!valid)
      {
        ++ignoredCount;
        continue;
      }
      while (pos < line.size() && line[pos] == ' ')
      {
        ++pos;
      }
      const std::string info = std::string(line.begin() + pos, line.end());
      if (info.empty())
      {
        ++ignoredCount;
        continue;
      }
      if (containsId(arr, id))
      {
        ++ignoredCount;
        continue;
      }
      pushBack(arr, Person{id, info});
    }
    return ParseResult{arr, ignoredCount};
  }
}
