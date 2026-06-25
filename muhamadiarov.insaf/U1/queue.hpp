#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"

namespace muhamadiarov
{
  template< class T >
  class Queue
  {
  public:
    bool empty() const noexcept;
    T& top() noexcept;
    void push(const T& val);
    void pop() noexcept;
    size_t size() const noexcept;
  private:
    List< T > data_;
  };
}

namespace muh = muhamadiarov;

template<class T>
bool muh::Queue< T >::empty() const noexcept
{
  if (data_.size() == 0)
  {
    return true;
  }
  return false;
}

template<class T>
T& muh::Queue< T >::top() noexcept
{
  return data_.head_->data_;
}

template<class T>
void muh::Queue< T >::push(const T& val)
{
  data_.pushBack(val);
}

template<class T>
void muh::Queue< T >::pop() noexcept
{
  data_.popFront();
}

template<class T>
size_t muh::Queue< T >::size() const noexcept
{
  return data_.size();
}
#endif
