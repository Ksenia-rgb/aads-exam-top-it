#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include "Person.hpp"
namespace lachugin
{
  void pushBack(Person*& persons, size_t& size, size_t& capacity, const Person& person);
  bool containsId(const Person* persons, size_t size, size_t id);
  bool parseLine(const std::string& line, Person& person);
}

#endif
