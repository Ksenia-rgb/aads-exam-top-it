#include "person.hpp"
#include <ostream>

bool borisov::containsId(const borisov::PersonNode * const head, const size_t id)
{
  const borisov::PersonNode *cur = head;
  while (cur != nullptr)
  {
    if (cur->data_.id_ == id)
    {
      return true;
    }
    cur = cur->next_;
  }
  return false;
}

void borisov::writePersons(std::ostream &out, const borisov::PersonNode * const head)
{
  const borisov::PersonNode *cur = head;
  while (cur != nullptr)
  {
    out << cur->data_.id_ << " " << cur->data_.info_ << "\n";
    cur = cur->next_;
  }
}

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
