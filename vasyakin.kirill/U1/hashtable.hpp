#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <utility>
#include "list.hpp"

namespace vasyakin
{
  template< class K >
  struct hashCell
  {
    K key;
  };

  template< class K >
  struct hashTable
  {
    listNode< hashCell< K > >** buckets;
    size_t cap;
    size_t size;
  };

  template< class K >
  size_t hashKey(K key, size_t cap)
  {
    return static_cast< size_t >(key) % cap;
  }

  template< class K >
  hashTable< K > makeHashTable(size_t cap)
  {
    hashTable< K > res{nullptr, cap == 0 ? 1 : cap, 0};
    res.buckets = new listNode< hashCell< K > >*[res.cap]{};

    return res;
  }

  template< class K >
  void clearHashTable(hashTable< K >& ht) noexcept
  {
    if (!ht.buckets)
    {
      return;
    }

    for (size_t i = 0; i < ht.cap; ++i)
    {
      clearList(ht.buckets[i]);
    }

    delete[] ht.buckets;
    ht.buckets = nullptr;
    ht.cap = 0;
    ht.size = 0;
  }

  template< class K >
  bool findInBucket(listNode< hashCell< K > >* head, K key)
  {
    for (listNode< hashCell< K > >* cur = head; cur; cur = cur->next)
    {
      if (cur->value.key == key)
      {
        return true;
      }
    }

    return false;
  }

  template< class K >
  bool containsHashTable(const hashTable< K >& ht, K key)
  {
    if (!ht.buckets)
    {
      return false;
    }

    size_t idx = hashKey(key, ht.cap);
    return findInBucket(ht.buckets[idx], key);
  }

  template< class K >
  bool insertHashTable(hashTable< K >& ht, K key)
  {
    size_t idx = hashKey(key, ht.cap);
    if (findInBucket(ht.buckets[idx], key))
    {
      return false;
    }

    ht.buckets[idx] = makeListNode(hashCell< K >{key}, ht.buckets[idx]);
    ++ht.size;

    return true;
  }
}

#endif
