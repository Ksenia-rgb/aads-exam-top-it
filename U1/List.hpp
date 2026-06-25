#ifndef LIST_HPP
#define LIST_HPP

namespace novikov
{
  template < class T > struct Node
  {
    T val;
    Node< T > *next;
  };

  template < class T > struct List
  {
    Node< T > *head;
  };
}

#endif
