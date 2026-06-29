#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

namespace muraviev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonNode
  {
    Person person;
    PersonNode* next;
  };

  struct PersonList
  {
    PersonNode* head;
    PersonNode* tail;
  };

  void initList(PersonList& list);
  void clearList(PersonList& list);
  bool hasPersonId(const PersonList& list, size_t id);
  void appendPerson(PersonList& list, const Person& person);
  bool parsePersonLine(const std::string& line, Person& person);
  void readPersons(std::istream& input, PersonList& persons,
      size_t& accepted, size_t& ignored);
  void printPersons(std::ostream& output, const PersonList& persons);
}

#endif
