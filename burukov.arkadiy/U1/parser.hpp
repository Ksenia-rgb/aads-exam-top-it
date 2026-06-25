#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "person.hpp"

namespace burukov
{

  bool parseLine(const std::string& line, Person& out);

}

#endif
