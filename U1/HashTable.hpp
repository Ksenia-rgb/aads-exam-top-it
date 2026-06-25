#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cstddef>
#include <functional>
#include <utility>

namespace novikov
{
  template < class T, class Key > struct HashNode
  {
    T val;
    Key key;
    HashNode *next;
  };

  template < class T, class Key, class Hash = std::hash< Key >, class Equal = std::equal_to< Key > > struct HashTable
  {
    HashNode< T, Key > **data;
    size_t size;
    size_t capacity;
    Hash hasher;
    Equal equal;
  };
}

#endif
