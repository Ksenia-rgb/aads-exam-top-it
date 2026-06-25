#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP

#include <cstddef>
#include <utility>

namespace shigarev {
  template< class T >
  struct DynArray {
    T* data_;
    size_t size_;
    size_t capacity_;
  };

  template< class T >
  DynArray< T > createDynArray(size_t capacity)
  {
    DynArray< T > result = {nullptr, 0, 0};
    if (capacity > 0) {
      result.data_ = new T[capacity];
      result.capacity_ = capacity;
    }
    return result;
  }

  template< class T >
  void destroyDynArray(DynArray< T >& arr)
  {
    delete[] arr.data_;
    arr.data_ = nullptr;
    arr.size_ = 0;
    arr.capacity_ = 0;
  }

  namespace detail {
    template< class T >
    void grow(DynArray< T >& arr)
    {
      const size_t newCap = (arr.capacity_ == 0) ? 4 : arr.capacity_ * 2;
      T* newData = new T[newCap];
      try {
        for (size_t i = 0; i < arr.size_; ++i) {
          newData[i] = std::move(arr.data_[i]);
        }
      } catch (...) {
        delete[] newData;
        throw;
      }
      delete[] arr.data_;
      arr.data_ = newData;
      arr.capacity_ = newCap;
    }
  }

  template< class T >
  void pushBack(DynArray< T >& arr, const T& value)
  {
    if (arr.size_ >= arr.capacity_) {
      detail::grow(arr);
    }
    arr.data_[arr.size_] = value;
    ++arr.size_;
  }

  template< class T >
  void pushBack(DynArray< T >& arr, T&& value)
  {
    if (arr.size_ >= arr.capacity_) {
      detail::grow(arr);
    }
    arr.data_[arr.size_] = std::move(value);
    ++arr.size_;
  }

  template< class T >
  const T& getAt(const DynArray< T >& arr, size_t index)
  {
    return arr.data_[index];
  }

  template< class T >
  T& getAt(DynArray< T >& arr, size_t index)
  {
    return arr.data_[index];
  }

  template< class T, class Pred >
  bool contains(const DynArray< T >& arr, Pred pred)
  {
    for (size_t i = 0; i < arr.size_; ++i) {
      if (pred(arr.data_[i])) {
        return true;
      }
    }
    return false;
  }
}

#endif
