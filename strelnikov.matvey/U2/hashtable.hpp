#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <cstddef>

namespace strelnikov
{

  template < typename K, typename V > struct HashNode
  {
    K key;
    V value;
    HashNode *next;
  };

  template < typename K, typename V > struct HashTable
  {
    HashNode< K, V > **buckets;
    size_t capacity;
    size_t size;
  };

  using HashFunc = size_t (*)(const void *);
  using EqFunc = bool (*)(const void *, const void *);

  size_t default_hash_size_t(const void *key)
  {
    return *(const size_t *)key;
  }

  bool default_eq_size_t(const void *a, const void *b)
  {
    return *(const size_t *)a == *(const size_t *)b;
  }

  template < typename K, typename V > void hash_init(HashTable< K, V > &table, size_t capacity)
  {
    table.capacity = capacity > 0 ? capacity : 16;
    table.size = 0;
    table.buckets = new HashNode< K, V > *[table.capacity]();
  }

  template < typename K, typename V > void hash_destroy(HashTable< K, V > &table)
  {
    for (size_t i = 0; i < table.capacity; ++i) {
      HashNode< K, V > *current = table.buckets[i];
      while (current != nullptr) {
        HashNode< K, V > *next = current->next;
        delete current;
        current = next;
      }
    }
    delete[] table.buckets;
    table.buckets = nullptr;
    table.capacity = 0;
    table.size = 0;
  }

  template < typename K, typename V >
  HashNode< K, V > *hash_find_node(HashTable< K, V > &table, const K &key, HashFunc hash, EqFunc eq)
  {
    size_t index = hash(&key) % table.capacity;
    HashNode< K, V > *current = table.buckets[index];
    while (current != nullptr) {
      if (eq(&current->key, &key)) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  template < typename K, typename V > V *hash_find(HashTable< K, V > &table, const K &key, HashFunc hash, EqFunc eq)
  {
    HashNode< K, V > *node = hash_find_node(table, key, hash, eq);
    if (node != nullptr) {
      return &node->value;
    }
    return nullptr;
  }

  template < typename K, typename V >
  void hash_insert(HashTable< K, V > &table, const K &key, const V &value, HashFunc hash, EqFunc eq)
  {
    size_t index = hash(&key) % table.capacity;
    HashNode< K, V > *current = table.buckets[index];
    while (current != nullptr) {
      if (eq(&current->key, &key)) {
        current->value = value;
        return;
      }
      current = current->next;
    }

    HashNode< K, V > *new_node = new HashNode< K, V >;
    new_node->key = key;
    new_node->value = value;
    new_node->next = table.buckets[index];
    table.buckets[index] = new_node;
    table.size++;
  }

  template < typename K, typename V > bool hash_remove(HashTable< K, V > &table, const K &key, HashFunc hash, EqFunc eq)
  {
    size_t index = hash(&key) % table.capacity;
    HashNode< K, V > *current = table.buckets[index];
    HashNode< K, V > *prev = nullptr;

    while (current != nullptr) {
      if (eq(&current->key, &key)) {
        if (prev == nullptr) {
          table.buckets[index] = current->next;
        } else {
          prev->next = current->next;
        }
        delete current;
        table.size--;
        return true;
      }
      prev = current;
      current = current->next;
    }
    return false;
  }

}

#endif
