#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>

namespace zharov
{
  namespace detail
  {
    template< class T >
    struct Node
    {
      T val;
      Node< T >* next;
      Node< T >* prev;
    };
  }

  template< class T >
  struct List
  {
    detail::Node< T >* head;
    detail::Node< T >* tail;
    size_t size;
  };

  template< class T >
  void clear(List< T >& lst);

  template< class T >
  detail::Node< T >* insert(List< T >& lst, detail::Node< T >* pos, const T& val);

  template< class T >
  void pushBack(List< T >& lst, const T& val);
}

template< class T >
void zharov::clear(List< T >& lst)
{
  detail::Node< T >* curr = lst.head;
  while (curr != nullptr)
  {
    detail::Node< T >* next = curr->next;
    delete curr;
    curr = next;
  }
  lst.head = nullptr;
  lst.tail = nullptr;
  lst.size = 0;
}

template< class T >
zharov::detail::Node< T >* zharov::insert(List< T >& lst, detail::Node< T >* pos, const T& val)
{
  detail::Node< T >* newNode = new detail::Node< T >{val, pos, pos ? pos->prev : lst.tail};
  if (newNode->prev)
  {
    newNode->prev->next = newNode;
  }
  else
  {
    lst.head = newNode;
  }
  if (newNode->next)
  {
    newNode->next->prev = newNode;
  }
  else
  {
    lst.tail = newNode;
  }
  ++lst.size;
  return newNode;
}

template< class T >
void zharov::pushBack(List< T >& lst, const T& val)
{
  insert(lst, static_cast< detail::Node< T >* >(nullptr), val);
}

#endif
