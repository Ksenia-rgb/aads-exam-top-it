#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
namespace zubarev
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

  struct HashSet
  {
    size_t* data;
    bool* used;
    size_t capacity;
  };
  void init(PersonArray& arr);
  void destroy(PersonArray& arr);
  void resize(PersonArray& arr);
  void push(PersonArray& arr, const Person& value);

}

#endif
