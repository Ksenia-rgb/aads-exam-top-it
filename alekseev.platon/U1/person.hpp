#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <string>

namespace alekseev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonArray
  {
    Person* data;
    size_t size;
    size_t capacity;
  };

  void initPersonArray(PersonArray& persons);
  void destroyPersonArray(PersonArray& persons);
}

#endif
