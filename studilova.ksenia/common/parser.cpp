#include "parser.hpp"

#include <cctype>

namespace
{
  bool isSpace(char symbol)
  {
    return std::isspace(static_cast< unsigned char >(symbol));
  }

  bool isDigit(char symbol)
  {
    return std::isdigit(static_cast< unsigned char >(symbol));
  }

  void skipSpaces(const std::string &line, size_t &position)
  {
    while ((position < line.size()) && isSpace(line[position]))
    {
      ++position;
    }
  }

  bool parseId(const std::string &line, size_t &position, size_t &id)
  {
    if ((position >= line.size()) || !isDigit(line[position]))
    {
      return false;
    }

    id = 0;
    while ((position < line.size()) && isDigit(line[position]))
    {
      id = id * 10 + static_cast< size_t >(line[position] - '0');
      ++position;
    }
    return true;
  }

   bool hasNoSpace(const std::string &line, size_t position)
  {
    while (position < line.size())
    {
      if (!isSpace(line[position]))
      {
        return true;
      }
      ++position;
    }
    return false;
  }
}

bool studilova::parsePersonLine(const std::string &line, Person &person)
{
  size_t position = 0;
  size_t id = 0;

  skipSpaces(line, position);

  if (!parseId(line, position, id))
  {
    return false;
  }

  if ((position >= line.size()) || !isSpace(line[position]))
  {
    return false;
  }

  skipSpaces(line, position);

  if (!hasNoSpace(line, position))
  {
    return false;
  }

  person.id_ = id;
  person.info_.clear();

  while (position < line.size())
  {
    person.info_ += line[position];
    ++position;
  }

  return true;
}
