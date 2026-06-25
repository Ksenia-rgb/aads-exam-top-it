#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <string>
#include <iosfwd>
#include "Array.hpp"

namespace yalovsky
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  void readPersons(std::istream& in, Array< Person >& persons, size_t& accepted, size_t& ignored);
  void printPersons(std::ostream& out, const Array< Person >& persons);
}

#endif
