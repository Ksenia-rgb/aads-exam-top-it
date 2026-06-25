#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <cstddef>
#include <iostream>
#include <string>

namespace pozdnyakov
{

  struct Person
  {
    size_t id;
    std::string info;
  };

  template< typename T >
  struct DynamicArray
  {
    T *data;
    size_t size;
    size_t capacity;
  };

  template< typename T >
  void initArray(DynamicArray< T > &arr)
  {
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
  }

  template< typename T >
  void destroyArray(DynamicArray< T > &arr)
  {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
  }
}

#endif
