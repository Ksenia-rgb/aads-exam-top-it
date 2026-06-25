#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

namespace vishnyakov
{

template< typename T >
struct ListNode
{
  T data;
  ListNode* next;

  ListNode(const T& value, ListNode* n = nullptr):
    data(value),
    next(n)
  {}
};

template< typename T >
class List
{
public:
  List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  List(const List& other):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    for (ListNode< T >* current = other.head_; current != nullptr; current = current->next)
    {
      pushBack(current->data);
    }
  }

  ~List()
  {
    clear();
  }

  List& operator=(const List& other)
  {
    if (this != &other)
    {
      List tmp(other);
      swap(tmp);
    }
    return *this;
  }

  ListNode< T >* begin() const
  {
    return head_;
  }

  ListNode< T >* end() const
  {
    return nullptr;
  }

  void pushBack(const T& value)
  {
    ListNode< T >* node = new ListNode< T >(value);
    if (empty())
    {
      head_ = node;
      tail_ = node;
    }
    else
    {
      tail_->next = node;
      tail_ = node;
    }
    ++size_;
  }

  void pushFront(const T& value)
  {
    head_ = new ListNode< T >(value, head_);
    if (empty())
    {
      tail_ = head_;
    }
    ++size_;
  }

  void popFront()
  {
    if (empty())
    {
      return;
    }
    ListNode< T >* temp = head_;
    head_ = head_->next;
    delete temp;
    --size_;
    if (empty())
    {
      tail_ = nullptr;
    }
  }

  bool empty() const
  {
    return size_ == 0;
  }

  size_t size() const
  {
    return size_;
  }

  void clear()
  {
    while (!empty())
    {
      popFront();
    }
  }

  void swap(List& other)
  {
    ListNode< T >* tempHead = head_;
    head_ = other.head_;
    other.head_ = tempHead;

    ListNode< T >* tempTail = tail_;
    tail_ = other.tail_;
    other.tail_ = tempTail;

    size_t tempSize = size_;
    size_ = other.size_;
    other.size_ = tempSize;
  }

private:
  ListNode< T >* head_;
  ListNode< T >* tail_;
  size_t size_;
};

}

#endif

