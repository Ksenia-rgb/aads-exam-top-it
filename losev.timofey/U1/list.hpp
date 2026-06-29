#ifndef LOSEV_LIST_HPP
#define LOSEV_LIST_HPP

#include "person.hpp"

namespace losev
{
  struct Node
  {
    Person data;
    Node* next;
  };

  Node* createNode(const Person& person);
  void pushBack(Node*& head, const Person& person);
  bool findId(const Node* head, size_t id);
  void clearList(Node*& head);
}

#endif
