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

  void freePersons(PersonNode *head);
}

#endif
