#include "person.hpp"
#include <istream>
#include <ostream>
#include <string>

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

borisov::PersonNode *borisov::readPersons(std::istream &in, size_t &count, size_t &skipped)
{
  borisov::PersonNode *head = nullptr;
  borisov::PersonNode *tail = nullptr;
  count = 0;
  skipped = 0;
  try
  {
    while (in)
    {
      size_t id = 0;
      if (!(in >> id))
      {
        if (in.eof())
        {
          break;
        }
        in.clear();
        std::string line;
        std::getline(in, line);
        ++skipped;
        continue;
      }
      std::string info;
      std::getline(in, info);
      size_t start = 0;
      while (start < info.size() && (info[start] == ' ' || info[start] == '\t'))
      {
        ++start;
      }
      if (start > 0)
      {
        info = info.substr(start);
      }
      if (info.empty() || borisov::containsId(head, id))
      {
        ++skipped;
        continue;
      }
      borisov::PersonNode * const node = new borisov::PersonNode{borisov::Person{id, info}, nullptr};
      if (tail == nullptr)
      {
        head = node;
        tail = node;
      }
      else
      {
        tail->next_ = node;
        tail = node;
      }
      ++count;
    }
  }
  catch (...)
  {
    borisov::freePersons(head);
    throw;
  }
  return head;
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
