#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "person.hpp"

namespace burukov
{

  enum ParseResult
  {
    PARSE_OK,
    PARSE_INVALID,
    PARSE_BLANK
  };

  ParseResult parseLine(const std::string& line, Person& out);

}

#endif
