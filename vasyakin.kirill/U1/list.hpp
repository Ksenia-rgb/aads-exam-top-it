#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>

namespace vasyakin
{
  template< class T >
  struct listNode
  {
    T value;
    listNode* next;
  };

  template< class T >
  listNode< T >* makeListNode(T val, listNode< T >* next)
  {
    return new listNode< T >{std::move(val), next};
  }

  template< class T >
  void clearList(listNode< T >* head) noexcept
  {
    while (head)
    {
      listNode< T >* next = head->next;
      delete head;
      head = next;
    }
  }

  template< class T >
  listNode< T >* copyList(const listNode< T >* head)
  {
    listNode< T >* resHead = nullptr;
    listNode< T >* resTail = nullptr;

    try
    {
      for (listNode< T >* cur = head; cur; cur = cur->next)
      {
        listNode< T >* node = makeListNode(cur->value, nullptr);

        if (!resHead)
        {
          resHead = node;
          resTail = node;
        }
        else
        {
          resTail->next = node;
          resTail = node;
        }
      }
    }
    catch (...)
    {
      clearList(resHead);
      throw;
    }

    return resHead;
  }
}

#endif
