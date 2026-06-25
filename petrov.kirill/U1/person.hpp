#ifndef PERSON_HPP
#define PERSON_HPP
#include <string>
#include <iostream>

namespace petrov
{
  struct Person
  {
    size_t id;
    std::string info;
  };
  void push_new(Person*& vec, size_t& s, size_t& c, Person p)
  {
    if (s == c)
    {
      size_t new_c = (c == 0) ? 2 : c * 2;
      Person* new_v = new Person[new_c];
      for (size_t i = 0; i < s; ++i)
      {
        new_v[i] = vec[i];
      }
      delete[] vec;
      vec = new_v;
      c = new_c;
    }
    vec[s++] = p;
  }

  size_t is_dubl(Person* vec, Person p, size_t s)
  {
    for (size_t i = 0; i < s; ++i)
    {
      if (vec[i].id == p.id) return 0;
    }
    return 1;
  }
}

#endif
