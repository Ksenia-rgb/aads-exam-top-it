#include "person.hpp"

void borisov::freePersons(borisov::PersonNode * const head)
{
  borisov::PersonNode *cur = head;
  while (cur != nullptr)
  {
    borisov::PersonNode * const next = cur->next_;
    delete cur;
    cur = next;
  }
}
