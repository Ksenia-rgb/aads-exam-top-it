#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
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
  bool parsePersonLine(const std::string& line, Person& person);
}

#endif
