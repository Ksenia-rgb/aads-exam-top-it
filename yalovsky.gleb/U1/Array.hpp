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
}

#endif
