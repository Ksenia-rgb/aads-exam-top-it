#ifndef LIST_HPP
#define LIST_HPP

namespace khalikov {
  template< class T >
  struct List
  {
    T val;
    List< T > *next;
  };

  template< class T >
  void pushBack(List< T > * h, const T &val)
  {
    List< T > *node = new List< T >;
    node->val = val;
    node->next = nullptr;
    if (!h) {
      h = node;
    }
    else {
      List< T > *curr = h;
      while (curr->next) {
        curr = curr->next;
      }
      curr->next = node;
    }
  }

  template< class T >
  void clear(List< T > * h)
  {
    List< T > * curr = h;
    while (curr) {
      List< T > *next = curr->next;
      delete curr;
      curr = next;
    }
    delete h;
  }

}
#endif
