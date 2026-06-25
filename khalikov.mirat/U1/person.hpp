#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include "list.hpp"
#include <iostream>

namespace khalikov {
  struct Person
  {
    size_t id;
    std::string info;
  };

  void getPerson(std::istream &in, List< Person > *&h)
  {
    Person p;
    p.id = 0;
    p.info = "";
    if (isdigit(in.peek())) {
      in >> p.id;
    }
    while (in.peek() == ' ') {
      in.get();
    }
    if (in.peek() == '\n') {
      in.get();
      return;
    }
    std::getline(in, p.info);
    khalikov::pushBack(h, p);
  }
}
#endif
