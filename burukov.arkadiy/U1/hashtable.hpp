#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cstddef>
#include <functional>

namespace burukov
{

  template< class K >
  struct hashNode
  {
    K key;
    hashNode< K >* next;
  };

  template< class K >
  struct hashTable
  {
    hashNode< K >** buckets;
    size_t size;
    size_t cap;
  };

  template< class K >
  size_t bucketIndex(const K& key, size_t cap)
  {
    return std::hash< K >{}(key) % cap;
  }

  template< class K >
  hashTable< K > makeHashTable(size_t cap)
  {
    size_t realCap = (cap == 0) ? 1 : cap;
    hashTable< K > res{nullptr, 0, realCap};
    res.buckets = new hashNode< K >*[realCap]{};
    return res;
  }

  template< class K >
  void clearHashTable(hashTable< K >& ht)
  {
    for (size_t i = 0; i < ht.cap; ++i)
    {
      hashNode< K >* cur = ht.buckets[i];
      while (cur)
      {
        hashNode< K >* next = cur->next;
        delete cur;
        cur = next;
      }
    }
    delete[] ht.buckets;
    ht.buckets = nullptr;
    ht.size = 0;
    ht.cap = 0;
  }

  template< class K >
  bool containsHashTable(const hashTable< K >& ht, const K& key)
  {
    if (ht.cap == 0)
    {
      return false;
    }
    const hashNode< K >* cur = ht.buckets[bucketIndex< K >(key, ht.cap)];
    while (cur)
    {
      if (cur->key == key)
      {
        return true;
      }
      cur = cur->next;
    }
    return false;
  }

  template< class K >
  void rehashHashTable(hashTable< K >& ht, size_t newCap)
  {
    size_t realCap = (newCap == 0) ? 1 : newCap;
    hashNode< K >** nb = new hashNode< K >*[realCap]{};
    for (size_t i = 0; i < ht.cap; ++i)
    {
      hashNode< K >* cur = ht.buckets[i];
      while (cur)
      {
        hashNode< K >* next = cur->next;
        size_t idx = bucketIndex< K >(cur->key, realCap);
        cur->next = nb[idx];
        nb[idx] = cur;
        cur = next;
      }
    }
    delete[] ht.buckets;
    ht.buckets = nb;
    ht.cap = realCap;
  }

  template< class K >
  bool insertHashTable(hashTable< K >& ht, const K& key)
  {
    if (containsHashTable(ht, key))
    {
      return false;
    }
    if ((ht.size + 1) * 10 >= ht.cap * 7)
    {
      rehashHashTable(ht, ht.cap * 2);
    }
    size_t idx = bucketIndex< K >(key, ht.cap);
    ht.buckets[idx] = new hashNode< K >{key, ht.buckets[idx]};
    ++ht.size;
    return true;
  }

}

#endif
