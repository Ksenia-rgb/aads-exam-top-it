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

  bool hasId(List< Person > *h, size_t id)
  {
    List< Person > *curr = h;
    while (curr) {
      if (curr->val.id == id) {
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  bool getPerson(std::istream &in, List< Person > *&h)
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
    if (in.peek() == '\n' || in.peek() == 't') {
      in.get();
      return false;
    }
    std::getline(in, p.info);
    if (hasId(h, p.id)) {
      return false;
    }
    khalikov::pushBack(h, p);
    return true;
  }
}
#endif
