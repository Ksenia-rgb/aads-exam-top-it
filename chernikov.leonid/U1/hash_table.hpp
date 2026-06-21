#ifndef CHERNIKOV_HASH_TABLE_HPP
#define CHERNIKOV_HASH_TABLE_HPP

#include <cstddef>
#include <utility>
#include <functional>

namespace chernikov
{

  template <class Key, class Value, class Hash = std::hash<Key>, class Equal = std::equal_to<Key>>
  class HashTable
  {
  public:
    struct Node
    {
      Key key;
      Value value;
      Node *next;
    };

    class Iterator
    {
    public:
      Iterator(Node **table, std::size_t slotCount, std::size_t currentSlot, Node *currentNode);

      std::pair<const Key &, Value &> operator*();
      Iterator &operator++();
      bool operator==(const Iterator &other) const;
      bool operator!=(const Iterator &other) const;

    private:
      Node **table_;
      std::size_t slotCount_;
      std::size_t currentSlot_;
      Node *currentNode_;

      void advanceToNext();
    };

    HashTable(std::size_t slotCount = 16);

    ~HashTable();

    HashTable(const HashTable &other) = delete;
    HashTable &operator=(const HashTable &other) = delete;

    void add(const Key &key, const Value &value);
    Value drop(const Key &key);
    bool has(const Key &key) const;
    Value &operator[](const Key &key);
    const Value &operator[](const Key &key) const;
    void rehash(std::size_t newSlotCount);

    Iterator begin();
    Iterator end();

    std::size_t size() const;
    std::size_t slotCount() const;
    bool empty() const;

  private:
    Node **table_;
    std::size_t slotCount_;
    std::size_t elementCount_;
    Hash hash_;
    Equal equal_;

    Node *findNode(const Key &key) const;
    std::size_t getSlot(const Key &key) const;
    void clear();
  };

}

#include "hash_table.cpp"

#endif
