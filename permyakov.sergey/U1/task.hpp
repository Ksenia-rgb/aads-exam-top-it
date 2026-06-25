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

  template< class T > void clear(list< T > lst);
  template< class T > list< T > * addAfter(list< T > lst);
  template< class T > void addToEnd(list< T > lst);
  std::pair< size_t, size_t > input(std::istream & in, list< Person > & lst);
  void output(std::osream & out, list< Person > & lst);
}

#endif
