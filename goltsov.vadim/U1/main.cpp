#include <iostream>
#include <string>
#include "hashtable.hpp"

namespace
{
  std::istream& skipSpaces(std::istream& is)
  {
    while (is.peek() == ' ')
    {
      is.get();
    }
    return is;
  }
  bool isEOL(std::istream& is)
  {
    if (is.peek() == '\n' || is.peek() == EOF)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

namespace goltsov
{
  std::pair< size_t, size_t > readPersons(HashTable& ht, std::istream& is, List** l)
  {
    size_t id;
    std::string info;
    List* start_l = *l;
    size_t good = 0, bad = 0;
    while (is)
    {
      if (is >> id)
      {
        skipSpaces(is);
        if (!isEOL(is))
        {
          is >> info;
          try
          {
            insertPerson(ht, id, {id, info});
            ++good;
            if (*l)
            {
              (*l)->next = newListNode(id, {id, info}, *l, nullptr);
              (*l) = (*l)->next;
            }
            else
            {
              *l = newListNode(id, {id, info}, *l, nullptr);
              start_l = *l;
            }
          }
          catch (...)
          {
            ++bad;
          }
        }
      }
    }
    *l = start_l;
    return {good, bad};
  }
  std::ostream& printRes(std::ostream& os, List* l)
  {
    while (l)
    {
      os << l->data.key << ' ' << l->data.value.info << '\n';
      l = l->next;
    }
    return os;
  }
}

int main()
{
  goltsov::HashTable ht = goltsov::newHT(100);
  goltsov::List* l = nullptr;
  std::istream& is = std::cin;
  std::ostream& os = std::cout;
  std::pair< size_t, size_t > res = goltsov::readPersons(ht, is, &l);
  goltsov::printRes(os, l);
  goltsov::deleteHashTable(ht);
  goltsov::deleteList(l);
}
