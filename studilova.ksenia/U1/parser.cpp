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
{}
