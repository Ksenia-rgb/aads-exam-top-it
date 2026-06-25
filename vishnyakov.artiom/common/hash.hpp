#ifndef HASH_HPP
#define HASH_HPP

#include <cstddef>
#include <utility>
#include <functional>

namespace vishnyakov
{

template< typename Key >
struct HashNode
{
  Key key;
  bool occupied;

  HashNode():
    key(),
    occupied(false)
  {}

  explicit HashNode(const Key& k):
    key(k),
    occupied(true)
  {}
};

template< typename Key >
class HashSet
{
public:
  HashSet():
    table_(nullptr),
    capacity_(16),
    size_(0)
  {
    table_ = new HashNode< Key >[capacity_];
  }

  explicit HashSet(size_t cap):
    table_(nullptr),
    capacity_(cap > 0 ? cap : 16),
    size_(0)
  {
    table_ = new HashNode< Key >[capacity_];
  }

  ~HashSet()
  {
    delete[] table_;
  }

  bool insert(const Key& key)
  {
    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      if (table_[idx].key == key)
      {
        return false;
      }
      idx = (idx + 1) % capacity_;
    }

    table_[idx] = HashNode< Key >(key);
    ++size_;

    if (static_cast< double >(size_) / capacity_ > 0.7)
    {
      rehash();
    }

    return true;
  }

  bool has(const Key& key) const
  {
    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      if (table_[idx].key == key)
      {
        return true;
      }
      idx = (idx + 1) % capacity_;
    }

    return false;
  }

private:
  HashNode< Key >* table_;
  size_t capacity_;
  size_t size_;

  size_t hash(const Key& key) const
  {
    return std::hash< Key >{}(key);
  }

  void rehash()
  {
    size_t newCap = capacity_ * 2;
    HashNode< Key >* newTable = new HashNode< Key >[newCap];

    for (size_t i = 0; i < capacity_; ++i)
    {
      if (table_[i].occupied)
      {
        size_t idx = hash(table_[i].key) % newCap;

        while (newTable[idx].occupied)
        {
          idx = (idx + 1) % newCap;
        }

        newTable[idx] = table_[i];
      }
    }

    delete[] table_;
    table_ = newTable;
    capacity_ = newCap;
  }
};

template< typename Key, typename Value >
class HashTable
{
public:
  struct Node
  {
    Key key;
    Value value;
    bool occupied;

    Node():
      key(),
      value(),
      occupied(false)
    {}

    Node(const Key& k, const Value& v):
      key(k),
      value(v),
      occupied(true)
    {}
  };

  HashTable():
    table_(nullptr),
    capacity_(16),
    size_(0)
  {
    table_ = new Node[capacity_];
  }

  explicit HashTable(size_t cap):
    table_(nullptr),
    capacity_(cap > 0 ? cap : 16),
    size_(0)
  {
    table_ = new Node[capacity_];
  }

  ~HashTable()
  {
    delete[] table_;
  }

  void add(const Key& key, const Value& value)
  {
    if (has(key))
    {
      return;
    }

    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      idx = (idx + 1) % capacity_;
    }

    table_[idx] = Node(key, value);
    ++size_;

    if (static_cast< double >(size_) / capacity_ > 0.7)
    {
      rehash();
    }
  }

  bool has(const Key& key) const
  {
    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      if (table_[idx].key == key)
      {
        return true;
      }
      idx = (idx + 1) % capacity_;
    }

    return false;
  }

  Value* find(const Key& key)
  {
    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      if (table_[idx].key == key)
      {
        return &table_[idx].value;
      }
      idx = (idx + 1) % capacity_;
    }

    return nullptr;
  }

  const Value* find(const Key& key) const
  {
    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      if (table_[idx].key == key)
      {
        return &table_[idx].value;
      }
      idx = (idx + 1) % capacity_;
    }

    return nullptr;
  }

  Value& operator[](const Key& key)
  {
    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      if (table_[idx].key == key)
      {
        return table_[idx].value;
      }
      idx = (idx + 1) % capacity_;
    }

    table_[idx] = Node(key, Value());
    ++size_;

    if (static_cast< double >(size_) / capacity_ > 0.7)
    {
      rehash();
    }

    size_t newIdx = hash(key) % capacity_;

    while (table_[newIdx].occupied)
    {
      if (table_[newIdx].key == key)
      {
        return table_[newIdx].value;
      }
      newIdx = (newIdx + 1) % capacity_;
    }

    return table_[newIdx].value;
  }

  void remove(const Key& key)
  {
    size_t idx = hash(key) % capacity_;

    while (table_[idx].occupied)
    {
      if (table_[idx].key == key)
      {
        table_[idx].occupied = false;
        --size_;
        return;
      }
      idx = (idx + 1) % capacity_;
    }
  }

  size_t size() const
  {
    return size_;
  }

private:
  Node* table_;
  size_t capacity_;
  size_t size_;

  size_t hash(const Key& key) const
  {
    return std::hash< Key >{}(key);
  }

  void rehash()
  {
    size_t newCap = capacity_ * 2;
    Node* newTable = new Node[newCap];

    for (size_t i = 0; i < capacity_; ++i)
    {
      if (table_[i].occupied)
      {
        size_t idx = hash(table_[i].key) % newCap;

        while (newTable[idx].occupied)
        {
          idx = (idx + 1) % newCap;
        }

        newTable[idx] = table_[i];
      }
    }

    delete[] table_;
    table_ = newTable;
    capacity_ = newCap;
  }
};

}

#endif

