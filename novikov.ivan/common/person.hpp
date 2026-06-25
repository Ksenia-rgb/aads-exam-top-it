#ifndef PERSON_HPP
#define PERSON_HPP
#include <iostream>

namespace novikov
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

  struct IdSet
  {
    size_t* data;
    bool* used;
    size_t capacity;
  };

  void create(PersonArray& arr);
  void drop(PersonArray& arr);
  void expand(PersonArray& arr);
  void push(PersonArray& arr, const Person& value);

  void create(IdSet& set);
  void drop(IdSet& set);
  size_t hash(const IdSet& set, size_t value);
  bool contains(const IdSet& set, size_t value);
  void insert(IdSet& set, size_t value);
}

#endif
