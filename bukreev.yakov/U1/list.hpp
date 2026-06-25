#ifndef LIST_HPP
#define LIST_HPP

namespace bukreev
{
  template< class T >
  struct List
  {
    T val;
    List< T >* next;
    List< T >* prev;
  };

  template< class T >
  void initList(List< T >* fake) noexcept
  {
    fake->next = fake;
    fake->prev = fake;
  }

  template< class T >
  void insertListHead(List< T >* fake, const T& val)
  {
    List< T >* newNode = new List< T >;
    newNode.val = val;

    newNode->prev = fake;
    newNode->next = fake->next;
    fake->next = newNode;
  }

  template< class T >
  void insertListTail(List< T >* fake, const T& val)
  {
    List< T >* newNode = new List< T >;
    newNode.val = val;

    newNode->next = fake;
    newNode->prev = fake->prev;
    fake->prev = newNode;
  }
}

#endif
