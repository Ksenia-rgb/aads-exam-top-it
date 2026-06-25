#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

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
    array.data = nullptr;
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
}

#endif
