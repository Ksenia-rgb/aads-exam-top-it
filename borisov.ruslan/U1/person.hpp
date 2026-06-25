#ifndef BORISOV_PERSON_HPP
#define BORISOV_PERSON_HPP
#include <cstddef>
#include <string>

namespace borisov
{
  struct Person
  {
    size_t id_;
    std::string info_;
  };

  struct PersonNode
  {
    Person data_;
    PersonNode *next_;
  };

  bool containsId(const PersonNode *head, size_t id);
  void freePersons(PersonNode *head);
}

#endif
