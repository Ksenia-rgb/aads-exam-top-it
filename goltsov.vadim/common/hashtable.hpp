#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <iosfwd>
#include <stdexcept>
#include "structPerson.hpp"
#include <functional>

namespace goltsov
{
  namespace detail
  {
    struct NodeHT
    {
      size_t key;
      Person value;
    };
  }
  struct List
  {
    detail::NodeHT data;
    List* prev;
    List* next;
  };
  void deleteList(List* current)
  {
    if (current)
    {
      if (current->prev)
      {
        while (current->prev)
        {
          current = current->prev;
        }
      }
      while (current)
      {
        List* for_delete = current;
        current = current->next;
        delete for_delete;
      }
    }
  }
  List* newListNode(size_t key, Person value, List* prev, List* next)
  {
    return new List{{key, value}, prev, next};
  }
  struct HashTable
  {
    List** data;
    size_t size;
  };
  HashTable newHT(size_t size)
  {
    HashTable ht;
    ht.data = new List*[size];
    for (size_t i = 0; i < size; ++i)
    {
      ht.data[i] = nullptr;
    }
    ht.size = size;
    return ht;
  }
  void deleteHashTable(HashTable& ht)
  {
    for (size_t i = 0; i < ht.size; ++i)
    {
      deleteList(ht.data[i]);
    }
    delete[] ht.data;
  }
  Person& getPerson(HashTable& ht, size_t id)
  {
    std::hash< size_t > hasher;
    size_t hash = hasher(id) % ht.size;
    List* node = ht.data[hash];
    while (node)
    {
      if (node->data.key == id)
      {
        return node->data.value;
      }
      node = node->next;
    }
    throw std::runtime_error("No key");
  }
  void insertPerson(HashTable& ht, size_t id, Person value)
  {
    std::hash< size_t > hasher;
    size_t hash = hasher(id) % ht.size;
    List* node = ht.data[hash];
    while (node && node->next)
    {
      if (node->data.key == id)
      {
        throw std::runtime_error("Key in table");
      }
      node = node->next;
    }
    if (node)
    {
      if (node->data.key == id)
      {
        throw std::runtime_error("Key in table");
      }
    }
    List* new_node = newListNode(id, value, node, nullptr);
    if (new_node->prev)
    {
      new_node->prev->next = new_node;
    }
    else
    {
      ht.data[hash] = new_node;
    }
  }
  void deletePerson(HashTable& ht, size_t id)
  {
    std::hash< size_t > hasher;
    size_t hash = hasher(id) % ht.size;
    List* node = ht.data[hash];
    while (node)
    {
      if (node->data.key == id)
      {
        if (node->next)
        {
          node->next->prev = node->prev;
        }
        if (node->prev)
        {
          node->prev->next = node->next;
        }
        else
        {
          ht.data[hash] = node->next;
        }
        delete node;
        return;
      }
      node = node->next;
    }
    throw std::runtime_error("No key");
  }
}

#endif

