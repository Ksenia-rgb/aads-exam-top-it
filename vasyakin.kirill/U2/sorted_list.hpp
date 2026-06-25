#ifndef SORTED_LIST_HPP
#define SORTED_LIST_HPP

namespace vasyakin
{
  template< class T >
  struct ListNode
  {
    T value;
    ListNode< T >* next;
  };

  template< class T >
  void clearList(ListNode< T > * node) noexcept
  {
    while (node != nullptr)
    {
      ListNode< T >* next = node->next;
      delete node;
      node = next;
    }
  }

  template< class T >
  void insertSorted(ListNode< T >*& head, const T& value)
  {
    ListNode< T > ** link = &head;
    while (*link != nullptr && !(value < (*link)->value))
    {
      link = std::addressof((*link)->next);
    }

    ListNode< T > * created = new ListNode< T >{ value, *link };
    *link = created;
  }
}

#endif
