#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cstddef>
#include <functional>
#include <utility>

namespace novikov
{
  template < class T, class Key >
  struct HashNode
  {
    T val;
    Key key;
    HashNode *next;
  };

  template < class T, class Key, class Hash = std::hash< Key >, class Equal = std::equal_to< Key > >
  struct HashTable
  {
    HashNode< T, Key > **data;
    size_t size;
    size_t capacity;
    Hash hasher;
    Equal equal;
  };

  template < class T, class Key, class Hash, class Equal >
  void insert(HashTable< T, Key, Hash, Equal > &table, const Key &key, const T &val)
  {
    size_t index = table.hasher(key) % table.capacity;
    HashNode< T, Key > *cur = table.data[index];
    while (cur) {
      if (table.equal(cur->key, key)) {
        cur->val = val;
        return;
      }
      cur = cur->next;
    }
    HashNode< T, Key > *node = new HashNode< T, Key >{val, key, table.data[index]};
    table.data[index] = node;
    table.size++;
  };

  template < class T, class Key, class Hash, class Equal >
  bool is_has(const HashTable< T, Key, Hash, Equal > &table, const Key &key)
  {
    size_t index = table.hasher(key) % table.capacity;
    HashNode< T, Key > *cur = table.data[index];
    while (cur) {
      if (table.equal(cur->key, key)) {
        return true;
      }
      cur = cur->next;
    }
    return false;
  };

  template < class T, class Key, class Hash, class Equal >
  void clear(HashTable< T, Key, Hash, Equal > &table)
  {
    for (size_t i = 0; i < table.capacity; ++i) {
      HashNode< T, Key > *cur = table.data[i];
      while (cur) {
        HashNode< T, Key > *next = cur->next;
        delete cur;
        cur = next;
      }
    }
    delete[] table.data;
    table.data = nullptr;
    table.capacity = 0;
    table.size = 0;
  };
}

#endif
