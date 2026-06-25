#include "parse.hpp"
#include "io.hpp"

#include <string>
#include <iostream>

namespace ulanova
{
  static bool readPerson(std::istream & in, Person & person)
  {
    size_t id = 0;
    if (!(in >> id))
    {
      in.clear();
      std::string skip;
      std::getline(in, skip);
      return false;
    }
    while (in.peek() == ' ' || in.peek() == '\t')
    {
      in.ignore();
    }
    std::string info;
    std::getline(in, info);
    if (info.empty())
    {
      return false;
    }
    person = Person{id, info};
    return true;
  }

  ParseResult readPersons(std::istream & in)
  {
    Array< Person > arr = mArray< Person >();
    size_t accepted = 0;
    size_t ignored = 0;
    in >> std::ws;
    while (!in.eof())
    {
      Person p{0, ""};
      if (readPerson(in, p) && !containsId(arr, p.id))
      {
        pushBack(arr, p);
        ++accepted;
      }
      else
      {
        ++ignored;
      }
      in >> std::ws;
    }
    return ParseResult{arr, accepted, ignored};
  }
}
