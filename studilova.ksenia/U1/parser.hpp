#ifndef STUDILOVA_PARSER_HPP
#define PARSER_HPP

#include <string>

#include "person.hpp"

namespace studilova
{
  bool parsePersonLine(const std::string &line, Person &person);
}

#endif
