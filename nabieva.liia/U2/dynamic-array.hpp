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
}

#endif
