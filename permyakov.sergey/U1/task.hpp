#ifndef TASK_HPP
#define TASK_HPP
#include <string>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <iostream>

namespace permyakov
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  template< class T > struct list
  {
    T data;
    list< T > * next;
  };

  template< class T > void clear(list< T > * lst)
  {
    while (lst->next) {
      list< T > * prv = lst;
      lst = lst->next;
      delete prv;
    }
    delete lst;
  }

  template< class T > list< T > * addAfter(list< T > * lst, const T val)
  {
    list< T > * nwNode = new list< T >();
    nwNode->data = val;
    nwNode->next = lst->next;
    lst->next = nwNode;
    return nwNode;
  }

  template< class T > void addToEnd(list< T > * lst, const T val)
  {
    list< T > * tmpLst = lst;
    while (tmpLst->next) {
      tmpLst = tmpLst->next;
    }
    addAfter(tmpLst, val);
  }

  std::pair< size_t, size_t > input(std::istream & in, list< Person > * lst)
  {
    std::pair< size_t, size_t > res = {0, 0};
    std::string line;
    while (std::getline(in, line)) {
      if (line.empty()) {
        res.second++;
        continue;
      }
      Person pers;
      std::string idP;
      std::string infoP;
      for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (!pers.id) {
          if (c != ' ') {
            idP += c;
          } else {
            try {
              pers.id = std::stoll(idP);
            } catch (...) {
              break;
            }
          }
        } else if (infoP.empty() && c == ' ') {
          continue;
        } else {
          infoP += c;
        }
      }
      if (!pers.id || pers.info.empty()) {
        res.second++;
        continue;
      }
      addToEnd(lst, pers);
      res.first++;
    }
    return res;
  }

  void output(std::ostream & out, list< Person > * lst)
  {
    list< Person > * tmpLst = lst;
    while (tmpLst->next) {
      out << tmpLst->data.id << ' ' << tmpLst->data.info << '\n';
      tmpLst = tmpLst->next;
    }
    out << tmpLst->data.id << ' ' << tmpLst->data.info << '\n';
  }
}

#endif
