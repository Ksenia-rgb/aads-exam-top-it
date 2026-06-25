#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <cstddef>
#include <iostream>

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
  bool isDuplicate(const personArr* array, size_t id);
  bool parseLine(const std::string& line, Person& person);
  void readPersons(std::istream& inStream, personArr* persons, size_t& successCount, size_t& ignoredCount);
  void writePersons(std::ostream& outStream, const personArr* persons);
}

#endif
