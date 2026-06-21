#include "input_parser.hpp"
#include <istream>
#include <ostream>
#include <cctype>
#include <string>

namespace
{

  bool isSpace(char c)
  {
    return c == ' ' || c == '\t';
  }

}

chernikov::Person chernikov::parseLine(const std::string &line, bool &success)
{
  success = false;
  Person person{0, ""};

  if (line.empty())
  {
    return person;
  }

  std::size_t pos = 0;
  std::size_t len = line.size();

  while (pos < len && isSpace(line[pos]))
  {
    ++pos;
  }

  if (pos >= len || !std::isdigit(line[pos]))
  {
    return person;
  }

  std::size_t id = 0;
  while (pos < len && std::isdigit(line[pos]))
  {
    id = id * 10 + (line[pos] - '0');
    ++pos;
  }

  person.id = id;

  while (pos < len && isSpace(line[pos]))
  {
    ++pos;
  }

  if (pos < len)
  {
    person.info = line.substr(pos);
  }

  if (person.info.empty())
  {
    return person;
  }

  success = true;
  return person;
}

chernikov::ParseResult chernikov::parseInput(std::istream &input, std::ostream &output)
{
  ParseResult result{0, 0};
  HashTable<std::size_t, bool, std::hash<std::size_t>, std::equal_to<std::size_t>> seenIds;

  std::string line;
  while (std::getline(input, line))
  {
    bool success = false;
    Person person = parseLine(line, success);

    if (!success)
    {
      ++result.ignoredCount;
      continue;
    }

    if (seenIds.has(person.id))
    {
      ++result.ignoredCount;
      continue;
    }

    seenIds.add(person.id, true);
    printPerson(person, output);
    ++result.validCount;
  }

  return result;
}
