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
}

bool studilova::parsePersonLine(const std::string &line, Person &person)
{}
