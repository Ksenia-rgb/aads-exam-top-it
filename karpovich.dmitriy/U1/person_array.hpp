#ifndef PERSON_ARRAY_HPP
#define PERSON_ARRAY_HPP

#include <cstddef>
#include "person.hpp"

namespace karpovich
{
  struct PersonArray
  {
    Person *data;
    size_t size;
    size_t capacity;
  };

  void initPersonArray(PersonArray &array);
  void destroyPersonArray(PersonArray &array);
  bool reservePersonArray(PersonArray &array, size_t capacity);
  bool containsPerson(const PersonArray &array, size_t id);
  bool pushBackPerson(PersonArray &array, const Person &person);
}

#endif
