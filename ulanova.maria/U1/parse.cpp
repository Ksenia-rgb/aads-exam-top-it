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
    in >> std::ws;
    while (!in.eof())
    {
      size_t id = 0;
      if (!(in >> id))
      {
        in.clear();
        std::string skip;
        std::getline(in, skip);
        ++ignoredCount;
        in >> std::ws;
        continue;
      }
      while (in.peek() == ' ' || in.peek() == '\t')
      {
        in.ignore();
      }
      std::string info;
      std::getline(in, info);
      if (info.empty())
      {
        ++ignoredCount;
        in >> std::ws;
        continue;
      }
      if (containsId(arr, id))
      {
        ++ignoredCount;
        in >> std::ws;
        continue;
      }
      pushBack(arr, Person{id, info});
      in >> std::ws;
    }
    return ParseResult{arr, ignoredCount};
  }
}
