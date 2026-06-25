#ifndef PERSON_OPS_HPP
#define PERSON_OPS_HPP

#include <person.hpp>

#include <cstddef>

namespace studilova
{
  Person *findPersonById(PersonArray &array, std::size_t id);
  const Person *findPersonById(const PersonArray &array, std::size_t id);
  void appendAnon(PersonArray &array, std::size_t id);
}

#endif
