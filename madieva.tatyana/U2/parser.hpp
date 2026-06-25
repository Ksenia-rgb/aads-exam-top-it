#ifndef PARSER_HPP
#define PARSER_HPP

#include "person.hpp"
#include "vector.hpp"
#include <string>

namespace madieva {

  bool parsePersonLine(const std::string & line, Person & person);
  bool parseMeetLine(const std::string & line, Meet & meet);

}

#endif
