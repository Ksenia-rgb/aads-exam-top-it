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
}

#endif
