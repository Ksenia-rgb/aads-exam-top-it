#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

namespace yalovsky
{
  template< class T >
  struct Array
  {
    T* data;
    size_t size;
    size_t capacity;
  };

  template< class T >
  Array< T > makeArray()
  {
    Array< T > result{nullptr, 0, 0};
    return result;
  }

  template< class T >
  void freeArray(Array< T >& arr)
  {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
  }

  template< class T >
  void reserveArray(Array< T >& arr, size_t newCapacity)
  {
    if (newCapacity <= arr.capacity)
    {
      return;
    }
    T* newData = new T[newCapacity];
    try
    {
      for (size_t i = 0; i < arr.size; ++i)
      {
        newData[i] = arr.data[i];
      }
    }
    catch (...)
    {
      delete[] newData;
      throw;
    }
    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCapacity;
  }

  template< class T >
  void pushBack(Array< T >& arr, const T& value)
  {
    if (arr.size == arr.capacity)
    {
      const size_t initialCapacity = 1;
      const size_t growthFactor = 2;
      const size_t grown = arr.capacity * growthFactor;
      const size_t newCapacity = (arr.capacity == 0) ? initialCapacity : grown;
      reserveArray(arr, newCapacity);
    }
    arr.data[arr.size] = value;
    ++arr.size;
  }

  template< class T >
  void removeAt(Array< T >& arr, size_t index)
  {
    for (size_t i = index + 1; i < arr.size; ++i)
    {
      arr.data[i - 1] = arr.data[i];
    }
    --arr.size;
  }
}

#endif
