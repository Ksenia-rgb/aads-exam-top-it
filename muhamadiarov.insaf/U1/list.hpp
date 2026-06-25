#ifndef LIST_HPP
#define LIST_HPP

namespace muhamadiarov
{
  template< class T >
  struct Node
  {
    T data_;
    Node< T >* next_;
    Node< T >* prev_;
    Node() = default;
  };
  template< class T >
  struct List
  {
    List() noexcept;
    void pushFront(const T& data);
    void popBack(const T& data) noexcept;
    size_t size() const noexcept;
  private
    Node< T >* head_;
    size_t size_;
  };
}

template< class T >
muh::List< T >::List() noexcept:
  head_(nullptr),
  size(0)
{}

template <class T>
void muh::List< T >::pushBack(const T& value)
{
  Node< T >* newNode = new Node< T >{value, nullptr, nullptr};
  try
  {
    if (!head_)
    {
      head_ = newNode;
      head_->next_ = head_;
      head_->prev_ = head_;
    }
    else
    {
      newNode->next_ = head_;
      newNode->prev_ = head_->prev_;
      head_->prev_->next_ = newNode;
      head_->prev_ = newNode;
    }
    ++size_;
  }
  catch(...)
  {
    delete newNode;
    throw;
  }
}

template <class T>
void muh::List< T >::popFront() noexcept
{
  if (!head_)
  {
    return;
  }

  if (size_ == 1)
  {
    delete head_;
    head_ = nullptr;
  }
  else
  {
    Node< T >* newHead = head_->next_;
    head_->prev_->next_ = newHead;
    newHead->prev_ = head_->prev_;
    delete head_;
    head_ = newHead;
  }
  --size_;
}

template< class T >
size_t size() const
{
  return size_;
}
#endif
