#ifndef AADS_EXAM_TOP_IT_HASHTABLE_HPP
#define AADS_EXAM_TOP_IT_HASHTABLE_HPP
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>

namespace kuznetsov {

  template< class K, class V >
  struct chainNode {
    K key;
    V value;
    chainNode< K, V >* next;
  };

  template< class K, class V >
  struct hashTable {
    chainNode< K, V >** buckets;
    size_t size, cap;
  };

  template< class K >
  size_t bucketIndex(const K& key, size_t cap)
  {
    return std::hash< K >{}(key) % cap;
  }

  template< class K, class V >
  hashTable< K, V > makeHashTable(size_t cap)
  {
    cap = cap < 1 ? 1 : cap;
    hashTable< K, V > res {nullptr, 0, cap};
    res.buckets = new chainNode< K, V >*[cap]{};
    return res;
  }

  template< class K, class V >
  void clearHashTable(hashTable< K, V >& ht)
  {
    for (size_t i = 0; i < ht.cap; ++i) {
      chainNode< K, V >* cur = ht.buckets[i];
      while (cur) {
        chainNode< K, V >* next = cur->next;
        delete cur;
        cur = next;
      }
    }
    delete[] ht.buckets;
    ht.buckets = nullptr;
    ht.size = 0;
    ht.cap = 0;
  }

  template< class K, class V >
  void rehashHashTable(hashTable< K, V >& ht, size_t newCap)
  {
    newCap = newCap < 1 ? 1 : newCap;
    chainNode< K, V >** nb = new chainNode< K, V >*[newCap]{};
    for (size_t i = 0; i < ht.cap; ++i) {
      chainNode< K, V >* cur = ht.buckets[i];
      while (cur) {
        chainNode< K, V >* next = cur->next;
        size_t idx = bucketIndex< K >(cur->key, newCap);
        cur->next = nb[idx];
        nb[idx] = cur;
        cur = next;
      }
    }
    delete[] ht.buckets;
    ht.buckets = nb;
    ht.cap = newCap;
  }

  template< class K, class V >
  chainNode< K, V >* findNode(hashTable< K, V >& ht, const K& key)
  {
    if (ht.cap == 0) {
      return nullptr;
    }
    size_t idx = bucketIndex< K >(key, ht.cap);
    chainNode< K, V >* cur = ht.buckets[idx];
    while (cur) {
      if (cur->key == key) {
        return cur;
      }
      cur = cur->next;
    }
    return nullptr;
  }

  template< class K, class V >
  V* findHashTable(hashTable< K, V >& ht, const K& key)
  {
    chainNode< K, V >* node = findNode(ht, key);
    return node ? &node->value : nullptr;
  }

  template< class K, class V >
  void insertHashTable(hashTable< K, V >& ht, K key, V val)
  {
    chainNode< K, V >* existing = findNode(ht, key);
    if (existing) {
      existing->value = std::move(val);
      return;
    }
    chainNode< K, V >* node = new chainNode< K, V >{std::move(key), std::move(val), nullptr};
    if ((ht.size + 1) * 10 >= ht.cap * 7) {
      try {
        rehashHashTable(ht, ht.cap * 2);
      } catch (...) {
        delete node;
        throw;
      }
    }
    size_t idx = bucketIndex< K >(node->key, ht.cap);
    node->next = ht.buckets[idx];
    ht.buckets[idx] = node;
    ++ht.size;
  }

  template< class K, class V >
  V& atHashTable(hashTable< K, V >& ht, const K& key)
  {
    V* v = findHashTable(ht, key);
    if (!v) {
      throw std::out_of_range("Key");
    }
    return *v;
  }

}

#endif

