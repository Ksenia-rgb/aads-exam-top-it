#ifndef PARSE_HPP
#define PARSE_HPP

#include "io.hpp"

#include <iostream>

namespace ulanova
{
  struct ParseResult
  {
    Array< Person > persons;
    size_t ignored;
  };

  ParseResult readPersons(std::istream & in);
}

#endif
