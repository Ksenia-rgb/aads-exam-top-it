#ifndef SAMARIN_COMMON_LIST_HPP
#define SAMARIN_COMMON_LIST_HPP

#include <memory>

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

    template < typename T, typename Compare >
    void insertSorted(list_t< T > & list, const T & value, Compare comesBefore)
    {
      list_node_t< T > ** link = std::addressof(list.head);
      while (*link != nullptr && comesBefore((*link)->value, value)) {
        link = std::addressof((*link)->next);
      }
      list_node_t< T > * const node = new list_node_t< T >{ value, *link };
      *link = node;
      if (node->next == nullptr) {
        list.tail = node;
      }
    }

    template < typename T, typename Predicate >
    void removeIf(list_t< T > & list, Predicate shouldRemove)
    {
      list_node_t< T > ** link = std::addressof(list.head);
      list_node_t< T > * tail = nullptr;
      while (*link != nullptr) {
        if (shouldRemove((*link)->value)) {
          list_node_t< T > * const dead = *link;
          *link = dead->next;
          delete dead;
        } else {
          tail = *link;
          link = std::addressof((*link)->next);
        }
      }
      list.tail = tail;
    }

    template < typename T, typename Predicate >
    const T * findValue(const list_t< T > & list, Predicate match)
    {
      for (const list_node_t< T > * node = list.head; node != nullptr; node = node->next) {
        if (match(node->value)) {
          return std::addressof(node->value);
        }
      }
      return nullptr;
    }

    template < typename T, typename Predicate >
    T * findValue(list_t< T > & list, Predicate match)
    {
      const list_t< T > & readable = list;
      return const_cast< T * >(findValue(readable, match));
    }
  }
}

#endif
