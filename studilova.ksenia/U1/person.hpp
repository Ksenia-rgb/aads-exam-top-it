#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <string>

namespace studilova
{
  struct Person
  {
    size_t id_;
    std::string info_;
  };

  struct PersonArray
  {
    Person* data_;
    size_t size_;
    size_t capacity_;
  };

  void initPersonArray(PersonArray &array);
  void destroyPersonArray(PersonArray &array);
  void appendPerson(PersonArray &array, const Person &person);
  bool containsPersonId(const PersonArray &array, std::size_t id);
}

#endif
