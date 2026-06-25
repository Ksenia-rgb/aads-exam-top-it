#ifndef SMIRNOVA_PARSE_LINE_HPP
#define SMIRNOVA_PARSE_LINE_HPP

#include <istream>
#include <string>
#include "person.hpp"

namespace smirnova
{
  bool parseLine(const std::string& line, size_t& id, std::string& info);

  template< typename T >
  bool hasPersonWithId(const T& persons, size_t id)
  {
    for (const auto& person : persons)
    {
      if (person.id == id)
      {
        return true;
      }
    }
    return false;
  }

  template< typename T >
  void processInput(std::istream& input, T& persons,
      size_t& validEntries, size_t& ignoredEntries)
  {
    std::string line;

    while (std::getline(input, line))
    {
      if (line.empty())
      {
        continue;
      }

      size_t id;
      std::string info;

      if (parseLine(line, id, info))
      {
        if (!hasPersonWithId(persons, id))
        {
          persons.push_back({ id, info });
          ++validEntries;
        }
        else
        {
          ++ignoredEntries;
        }
      }
      else
      {
        ++ignoredEntries;
      }
    }
  }

  template< typename T >
  void printPersons(const T& persons, std::ostream& out)
  {
    for (const auto& person : persons)
    {
      out << person.id << ' ' << person.info << '\n';
    }
  }
}

#endif
