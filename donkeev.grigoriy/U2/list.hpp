#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <string>

namespace donkeev
{
struct Person
  {
      size_t id;
      std::string info;
  };

  struct PersonNode
  {
    Person* data;
    PersonNode* next_;
    PersonNode* prev_;
  };

  struct PersonList
  {
    PersonNode* head_;
    PersonNode* tail_;
    size_t size_;
  };

}

#endif
