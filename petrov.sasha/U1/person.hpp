#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <cstddef>

namespace petrov
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct personArr
  {
    Person* data;
    size_t size;
    size_t capacity;
  };

  personArr* createPersonArray(size_t capacity);
  void destroyPersonArray(personArr* array);
  void pushPerson(personArr* array, const Person& person);
}

#endif

