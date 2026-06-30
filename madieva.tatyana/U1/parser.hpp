#ifndef PARSER_HPP
#define PARSER_HPP

#include "person.hpp"
#include <string>

namespace madieva {

  bool parseLine(const std::string & line, Person & person);

}

#endif
