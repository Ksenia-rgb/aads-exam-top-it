#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <limits>
#include <stdexcept>

namespace lukashevich
{
  namespace detail
  {
    const size_t INITIAL_ARRAY_CAPACITY = 4;
  }

  template< class T >
  struct Array
  {
    T* data_;
    size_t size_;
    size_t capacity_;
  };

  template< class T >
  void initArray(Array< T >& array) noexcept
  {
    array.data_ = nullptr;
    array.size_ = 0;
    array.capacity_ = 0;
  }

  template< class T >
  void destroyArray(Array< T >& array) noexcept
  {
    delete[] array.data_;
    array.data_ = nullptr;
    array.size_ = 0;
    array.capacity_ = 0;
  }

  template< class T >
  void resArray(Array< T >& array, size_t newCapacity)
  {
    if (newCapacity <= array.capacity_) {
      return;
    }

    T* newData = new T[newCapacity];

    try {
      for (size_t i = 0; i < array.size_; ++i) {
        newData[i] = array.data_[i];
      }
    } catch (...) {
      delete[] newData;
      throw;
    }

    delete[] array.data_;
    array.data_ = newData;
    array.capacity_ = newCapacity;
  }

  template< class T >
  void eraseAt(Array< T >& array, size_t index)
  {
    if (index >= array.size_) {
      return;
    }

    for (size_t i = index; i + 1 < array.size_; ++i) {
      array.data_[i] = array.data_[i + 1];
    }

    --array.size_;
  }

  template < class T >
  void pushBack(Array< T >& array, const T& value)
  {
    if (array.size_ == array.capacity_) {
      size_t newCapacity = detail:: INITIAL_ARRAY_CAPACITY;

      if (array.capacity_ != 0) {
        const size_t maxCapacity = std::numeric_limits< size_t >::max() / 2;

        if (array.capacity_ > maxCapacity) {
          throw std::length_error("overflow capacity");
        }

        newCapacity = array.capacity_ * 2;
      }

      resArray(array, newCapacity);
    }

    array.data_[array.size_] = value;
    ++array.size_;
  }
}

#endif
