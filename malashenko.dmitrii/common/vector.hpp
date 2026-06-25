#include <iostream>
#include <cstddef>
#include <fstream>
#include <string>


namespace malashenko
{
  template< class T >
  struct Vec {
    T* data;
    size_t size, capacity;
  };

  template< class T >
  void init(Vec< T >& vec, size_t cap)
  {
    vec.data = new T[cap];
    vec.capacity = cap;
    vec.size = 0;
  }

  template< class T >
  void pushBack(Vec< T >& vec, T val)
  {
    if (vec.size >= vec.capacity)
    {
      size_t new_capacity = vec.capacity * 2;
      T* new_data = new T[new_capacity];
      for (size_t i = 0; i < vec.size; ++i)
      {
        new_data[i] = vec.data[i];
      }
      delete[] vec.data;
      vec.data = new_data;
      vec.capacity = new_capacity;
    }
    vec.data[vec.size++] = val;
  }

  template <typename T>
  void destroy(Vec< T >& vec)
  {
    delete[] vec.data;
    vec.data = nullptr;
    vec.size = 0;
    vec.capacity = 0;
  }
}
