#ifndef TASK_HPP
#define TASK_HPP
#include <string>
#include <cstddef>
#include <utility>

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

  template< class T > void clear(list< T > lst)
  {
    list< T > * tmpLst = lst;
    while (tmpLst->next) {
      list< T > * prv = tmpLst;
      tmpLlst = rmpLst->next;
      delete prv;
    }
    delete tmpLst;
  }

  template< class T > list< T > * addAfter(list< T > & lst, const T val)
  {
    list< T > * nwNode = new list< T >();
    nwNode->data = val;
    nwNode->next = lst->next;
    lst->next = nwNode;
    return nwNode;
  }

  template< class T > void addToEnd(list< T > & lst, const T val)
  {
    list< T > * tmpLst = lst;
    while (tmpLst->next) {
      tmpLst = tmpLst->next;
    }
    addAfter(tmpLst, val);
  }

  std::pair< size_t, size_t > input(std::istream & in, list< Person > & lst);
  void output(std::osream & out, list< Person > & lst);
}

#endif
