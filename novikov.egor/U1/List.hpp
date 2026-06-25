#ifndef LIST_HPP
#define LIST_HPP

namespace novikov
{
  template < class T >
  struct Node
  {
    T val;
    Node< T > *next;
  };

  template < class T >
  struct List
  {
    Node< T > *head;
  };

  template < class T >
  void push_back(List< T > &list, const T &val)
  {
    Node< T > *node = new Node< T >{val, nullptr};
    if (!list.head) {
      list.head = node;
    } else {
      Node< T > *cur = list.head;
      while (cur->next) {
        cur = cur->next;
      }
      cur->next = node;
    }
  };

  template < class T >
  void clear(List< T > &list)
  {
    Node< T > *cur = list.head;
    while (cur) {
      Node< T > *next = cur->next;
      delete cur;
      cur = next;
    }
    list.head = nullptr;
  };
}
#endif
