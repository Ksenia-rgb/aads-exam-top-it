#ifndef SORTED_LIST_HPP
#define SORTED_LIST_HPP

namespace sedov
{
  template< typename T >
  struct ListNode
  {
    T value;
    ListNode< T > * next;
  };

  template< typename T >
  void clearList(ListNode< T > * node) noexcept
  {
    while (node != nullptr)
    {
      ListNode< T > * next = node->next;
      delete node;
      node = next;
    }
  }

  template< typename T >
  void insertSorted(ListNode< T > *& head, const T & value)
  {
    ListNode< T > ** link = &head;
    while (*link != nullptr && !(value < (*link)->value))
    {
      link = &(*link)->next;
    }
    ListNode< T > * created = new ListNode< T >{ value, *link };
    *link = created;
  }
}

#endif
