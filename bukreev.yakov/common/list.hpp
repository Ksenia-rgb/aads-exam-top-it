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
  void createList(List< T >** ppfake)
  {
    *ppfake = new List< T >;
    List< T >* pfake = *ppfake;
    pfake->next = pfake;
    pfake->prev = pfake;
  }

  template< class T >
  void deleteList(List< T >* fake)
  {
    List< T >* h = fake->next;
    while (h != fake)
    {
      List< T >* n = h->next;
      delete h;
      h = n;
    }

    delete fake;
  }

  template< class T >
  void insertListHead(List< T >* fake, const T& val)
  {
    List< T >* newNode = new List< T >;
    newNode->val = val;

    newNode->prev = fake;
    newNode->next = fake->next;
    newNode->next->prev = newNode;
    fake->next = newNode;
  }

  template< class T >
  void insertListTail(List< T >* fake, const T& val)
  {
    List< T >* newNode = new List< T >;
    newNode->val = val;

    newNode->next = fake;
    newNode->prev = fake->prev;
    newNode->prev->next = newNode;
    fake->prev = newNode;
  }
}

#endif
