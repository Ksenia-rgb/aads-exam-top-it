#ifndef MUSORIN_LIST_HPP
#define MUSORIN_LIST_HPP
#include <cstddef>
namespace musorin
{
namespace detail
{
template< class T >
struct Node
{
  T value;
  Node< T > * next;
};
}
template< class T >
struct List
{
  detail::Node< T > * head;
  detail::Node< T > * tail;
  std::size_t size;
};
template< class T >
void initList(List< T > & list)
{
  list.head = nullptr;
  list.tail = nullptr;
  list.size = 0;
}
template< class T >
bool isEmpty(const List< T > & list)
{
  return list.size == 0;
}
template< class T >
void pushBack(List< T > & list, const T & value)
{
  detail::Node< T > * node = new detail::Node< T >;
  node->value = value;
  node->next = nullptr;
  if (list.tail == nullptr)
  {
    list.head = node;
    list.tail = node;
  }
  else
  {
    list.tail->next = node;
    list.tail = node;
  }
  ++list.size;
}
template< class T >
void clear(List< T > & list)
{
  detail::Node< T > * current = list.head;
  while (current != nullptr)
  {
    detail::Node< T > * next = current->next;
    delete current;
    current = next;
  }
  list.head = nullptr;
  list.tail = nullptr;
  list.size = 0;
}
template< class T, class Pred >
void removeIf(List< T > & list, Pred pred)
{
  detail::Node< T > * current = list.head;
  detail::Node< T > * previous = nullptr;
  while (current != nullptr)
  {
    detail::Node< T > * next = current->next;
    if (pred(current->value))
    {
      if (previous == nullptr)
      {
        list.head = next;
      }
      else
      {
        previous->next = next;
      }
      if (next == nullptr)
      {
        list.tail = previous;
      }
      delete current;
      --list.size;
    }
    else
    {
      previous = current;
    }
    current = next;
  }
}
}
#endif
