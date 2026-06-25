#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <cstddef>
#include <functional>

namespace burukov
{

  template< class K, class V >
  struct mapNode
  {
    K key;
    V value;
    mapNode< K, V >* next;
  };

  template< class K, class V >
  struct hashMap
  {
    mapNode< K, V >** buckets;
    size_t size;
    size_t cap;
  };

  template< class K, class V >
  size_t mapBucketIndex(const K& key, size_t cap)
  {
    return std::hash< K >{}(key) % cap;
  }

  template< class K, class V >
  hashMap< K, V > makeHashMap(size_t cap)
  {
    size_t realCap = (cap == 0) ? 1 : cap;
    hashMap< K, V > res{nullptr, 0, realCap};
    res.buckets = new mapNode< K, V >*[realCap]{};
    return res;
  }

  template< class K, class V >
  void clearHashMap(hashMap< K, V >& hm)
  {
    for (size_t i = 0; i < hm.cap; ++i)
    {
      mapNode< K, V >* cur = hm.buckets[i];
      while (cur)
      {
        mapNode< K, V >* next = cur->next;
        delete cur;
        cur = next;
      }
    }
    delete[] hm.buckets;
    hm.buckets = nullptr;
    hm.size = 0;
    hm.cap = 0;
  }

  template< class K, class V >
  V* findHashMap(const hashMap< K, V >& hm, const K& key)
  {
    if (hm.cap == 0)
    {
      return nullptr;
    }
    mapNode< K, V >* cur = hm.buckets[mapBucketIndex< K, V >(key, hm.cap)];
    while (cur)
    {
      if (cur->key == key)
      {
        return std::addressof(cur->value);
      }
      cur = cur->next;
    }
    return nullptr;
  }

  template< class K, class V >
  void rehashHashMap(hashMap< K, V >& hm, size_t newCap)
  {
    size_t realCap = (newCap == 0) ? 1 : newCap;
    mapNode< K, V >** nb = new mapNode< K, V >*[realCap]{};
    for (size_t i = 0; i < hm.cap; ++i)
    {
      mapNode< K, V >* cur = hm.buckets[i];
      while (cur)
      {
        mapNode< K, V >* next = cur->next;
        size_t idx = mapBucketIndex< K, V >(cur->key, realCap);
        cur->next = nb[idx];
        nb[idx] = cur;
        cur = next;
      }
    }
    delete[] hm.buckets;
    hm.buckets = nb;
    hm.cap = realCap;
  }

  template< class K, class V >
  V* insertHashMap(hashMap< K, V >& hm, const K& key, const V& value)
  {
    V* existing = findHashMap(hm, key);
    if (existing)
    {
      return existing;
    }
    if ((hm.size + 1) * 10 >= hm.cap * 7)
    {
      rehashHashMap(hm, hm.cap * 2);
    }
    size_t idx = mapBucketIndex< K, V >(key, hm.cap);
    hm.buckets[idx] = new mapNode< K, V >{key, value, hm.buckets[idx]};
    ++hm.size;
    return std::addressof(hm.buckets[idx]->value);
  }

}

#endif
