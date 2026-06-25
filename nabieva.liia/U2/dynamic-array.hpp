#ifndef KIRILICH_DYNAMIC_ARRAY_HPP
#define KIRILICH_DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>

namespace nabieva
{
  template< typename T >
  struct DynamicArray
  {
    T* data;
    std::size_t size;
    std::size_t capacity;
  };

  template< typename T >
  void init(DynamicArray< T >& array)
  {
    array.data = 0;
    array.size = 0;
    array.capacity = 0;
  }

  template< typename T >
  void clear(DynamicArray< T >& array)
  {
    delete[] array.data;
    array.data = 0;
    array.size = 0;
    array.capacity = 0;
  }

  template< typename T >
  void reserve(DynamicArray< T >& array, std::size_t newCapacity)
  {
    if (newCapacity <= array.capacity)
    {
      return;
    }

    T* newData = new T[newCapacity];
    try
    {
      for (std::size_t i = 0; i < array.size; ++i)
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
    array.capacity = newCapacity;
  }

  template< typename T >
  void pushBack(DynamicArray< T >& array, const T& value)
  {
    if (array.size == array.capacity)
    {
      const std::size_t newCapacity = (array.capacity == 0 ? 4 : array.capacity * 2);
      reserve(array, newCapacity);
    }
    array.data[array.size] = value;
    ++array.size;
  }
}

#endif
