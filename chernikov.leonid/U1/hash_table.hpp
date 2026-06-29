#ifndef CHERNIKOV_HASH_TABLE_HPP
#define CHERNIKOV_HASH_TABLE_HPP

#include <cstddef>
#include <utility>
#include <functional>
#include <stdexcept>

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
      Iterator(Node **table, std::size_t slotCount, std::size_t currentSlot, Node *currentNode) : table_(table),
                                                                                                  slotCount_(slotCount),
                                                                                                  currentSlot_(currentSlot),
                                                                                                  currentNode_(currentNode)
      {
        if (currentNode_ == nullptr)
        {
          advanceToNext();
        }
      }

      std::pair<const Key &, Value &> operator*()
      {
        return {currentNode_->key, currentNode_->value};
      }

      Iterator &operator++()
      {
        if (currentNode_ != nullptr)
        {
          currentNode_ = currentNode_->next;
        }
        advanceToNext();
        return *this;
      }

      bool operator==(const Iterator &other) const
      {
        return (currentSlot_ == other.currentSlot_ && currentNode_ == other.currentNode_);
      }

      bool operator!=(const Iterator &other) const
      {
        return !(*this == other);
      }

    private:
      Node **table_;
      std::size_t slotCount_;
      std::size_t currentSlot_;
      Node *currentNode_;

      void advanceToNext()
      {
        if (currentNode_ != nullptr)
        {
          return;
        }

        while (currentSlot_ < slotCount_ && table_[currentSlot_] == nullptr)
        {
          ++currentSlot_;
        }

        if (currentSlot_ < slotCount_)
        {
          currentNode_ = table_[currentSlot_];
        }
      }
    };

    HashTable(std::size_t slotCount = 16) : table_(new Node *[slotCount]()),
                                            slotCount_(slotCount),
                                            elementCount_(0)
    {
    }

    ~HashTable()
    {
      clear();
    }

    HashTable(const HashTable &other) = delete;
    HashTable &operator=(const HashTable &other) = delete;

    void add(const Key &key, const Value &value)
    {
      Node *existingNode = findNode(key);
      if (existingNode != nullptr)
      {
        existingNode->value = value;
        return;
      }

      std::size_t slot = getSlot(key);
      Node *newNode = new Node{key, value, table_[slot]};
      table_[slot] = newNode;
      ++elementCount_;
    }

    Value drop(const Key &key)
    {
      std::size_t slot = getSlot(key);
      Node *current = table_[slot];
      Node *prev = nullptr;

      while (current != nullptr && !equal_(current->key, key))
      {
        prev = current;
        current = current->next;
      }

      if (current == nullptr)
      {
        throw std::out_of_range("Key not found");
      }

      if (prev == nullptr)
      {
        table_[slot] = current->next;
      }
      else
      {
        prev->next = current->next;
      }

      Value droppedValue = current->value;
      delete current;
      --elementCount_;
      return droppedValue;
    }

    bool has(const Key &key) const
    {
      return findNode(key) != nullptr;
    }

    Value &operator[](const Key &key)
    {
      Node *node = findNode(key);
      if (node == nullptr)
      {
        add(key, Value{});
        node = findNode(key);
      }
      return node->value;
    }

    const Value &operator[](const Key &key) const
    {
      Node *node = findNode(key);
      if (node == nullptr)
      {
        throw std::out_of_range("Key not found");
      }
      return node->value;
    }

    void rehash(std::size_t newSlotCount)
    {
      Node **oldTable = table_;
      std::size_t oldSlotCount = slotCount_;

      table_ = new Node *[newSlotCount]();
      slotCount_ = newSlotCount;

      for (std::size_t i = 0; i < oldSlotCount; ++i)
      {
        Node *current = oldTable[i];
        while (current != nullptr)
        {
          Node *next = current->next;
          std::size_t newSlot = getSlot(current->key);
          current->next = table_[newSlot];
          table_[newSlot] = current;
          current = next;
        }
      }

      delete[] oldTable;
    }

    Iterator begin()
    {
      return Iterator(table_, slotCount_, 0, nullptr);
    }

    Iterator end()
    {
      return Iterator(table_, slotCount_, slotCount_, nullptr);
    }

    std::size_t size() const
    {
      return elementCount_;
    }

    std::size_t slotCount() const
    {
      return slotCount_;
    }

    bool empty() const
    {
      return elementCount_ == 0;
    }

  private:
    Node **table_;
    std::size_t slotCount_;
    std::size_t elementCount_;
    Hash hash_;
    Equal equal_;

    Node *findNode(const Key &key) const
    {
      std::size_t slot = getSlot(key);
      Node *current = table_[slot];
      while (current != nullptr)
      {
        if (equal_(current->key, key))
        {
          return current;
        }
        current = current->next;
      }
      return nullptr;
    }

    std::size_t getSlot(const Key &key) const
    {
      return hash_(key) % slotCount_;
    }

    void clear()
    {
      for (std::size_t i = 0; i < slotCount_; ++i)
      {
        Node *current = table_[i];
        while (current != nullptr)
        {
          Node *next = current->next;
          delete current;
          current = next;
        }
      }
      delete[] table_;
    }
  };

}

#endif
