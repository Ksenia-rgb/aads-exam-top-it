#ifndef SAMARIN_COMMON_LIST_HPP
#define SAMARIN_COMMON_LIST_HPP

namespace samarin {
  namespace detail {
    template < typename T >
    struct list_node_t {
      T value;
      list_node_t< T > * next;
    };

    template < typename T >
    struct list_t {
      list_node_t< T > * head;
      list_node_t< T > * tail;
    };

    template < typename T >
    void pushBack(list_t< T > & list, const T & value)
    {
      list_node_t< T > * const node = new list_node_t< T >{ value, nullptr };
      if (list.head == nullptr) {
        list.head = node;
      } else {
        list.tail->next = node;
      }
      list.tail = node;
    }

    template < typename T >
    void clear(list_t< T > & list)
    {
      list_node_t< T > * node = list.head;
      while (node != nullptr) {
        list_node_t< T > * const next = node->next;
        delete node;
        node = next;
      }
      list.head = nullptr;
      list.tail = nullptr;
    }
  }
}

#endif
