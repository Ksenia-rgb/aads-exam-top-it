#ifndef PARSER_HPP
#define PARSER_HPP

#include "person.hpp"

namespace vasyakin
{
  bool parseLine(const std::string& line, Person& person);
}

#endif
