#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>

namespace zhuravleva
{
  template< class T >
  struct DynamicArray
  {
    T *data;
    size_t size;
    size_t capacity;
  };

  template< class T >
  void init(DynamicArray< T > &array)
  {
    array.data = nullptr;
    array.size = 0;
    array.capacity = 0;
  }

  template< class T >
  void destroy(DynamicArray< T > &array)
  {
    delete[] array.data;
    array.data = nullptr;
    array.size = 0;
    array.capacity = 0;
  }

  template< class T >
  void reserve(DynamicArray< T > &array, size_t capacity)
  {
    if (capacity <= array.capacity)
    {
      return;
    }
    T *newData = new T[capacity];
    try
    {
      for (size_t i = 0; i < array.size; ++i)
      {
        newData[i] = array.data[i];
      }
    }
    catch (...)
    {
      delete[] newData;
      throw;
    }
    delete[] array.data;
    array.data = newData;
    array.capacity = capacity;
  }

  template< class T >
  void pushBack(DynamicArray< T > &array, const T &value)
  {
    const size_t defaultCapacity = 8;
    if (array.size == array.capacity)
    {
      const size_t newCapacity =
          (array.capacity == 0) ? defaultCapacity : array.capacity * 2;

      reserve(array, newCapacity);
    }
    array.data[array.size] = value;
    ++array.size;
  }
}

#endif
