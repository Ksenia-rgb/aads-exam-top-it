#ifndef PERSON_IO_HPP
#define PERSON_IO_HPP
#include <iosfwd>
#include "person.hpp"

namespace sedov
{
  std::istream & readPerson(std::istream & in, Person & person, bool & valid);
  std::ostream & writePerson(std::ostream & out, const Person & person);
}

#endif
