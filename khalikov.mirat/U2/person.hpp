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

  struct Meet
  {
    size_t id1;
    size_t id2;
    size_t time;
  }

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

  bool getMeet(std::istream &in, List< Meet > *&h)
  {
    size_t id1 = 0;
    size_t id2 = 0;
    size_t time = 0;
    if (!(in >> id1 >> id2 >> time)) {
      return false;
    }
    if (id1 == id2) {
      return true;
    }
    Meet m{id1, id2, time};
    khalikov::pushBack(h, m);
    return true;
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
