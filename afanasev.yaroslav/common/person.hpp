#ifndef AFANASEV_PERSON_HPP
#define AFANASEV_PERSON_HPP

#include <string>

namespace afanasev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  bool parseLine(const std::string& line, Person& person);
  void addPerson(Person*& persons, size_t& count, size_t& capacity, const Person& person);
  bool existsPerson(const Person* persons, size_t count, size_t id);
}

#endif
