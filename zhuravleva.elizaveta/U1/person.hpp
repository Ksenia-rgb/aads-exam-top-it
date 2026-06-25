#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <string>

namespace zhuravleva
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonArray
  {
    Person *data;
    size_t size;
    size_t capacity;
  };

  void init(PersonArray &persons);
  void destroy(PersonArray &persons);
  void reserve(PersonArray &persons, size_t capacity);
  void pushBack(PersonArray &persons, const Person &person);
  bool contains(const PersonArray &persons, size_t id);
}

#endif
