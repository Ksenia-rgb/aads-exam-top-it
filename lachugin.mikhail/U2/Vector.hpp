#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>

namespace lachugin
{
  template< class T >
  struct Vector
  {
    T* data;
    size_t size;
    size_t capacity;
  };

  template< class T >
  void initVector(Vector< T >& vector)
  {
    vector.data = new T[8];
    vector.size = 0;
    vector.capacity = 8;
  }

  template< class T >
  void pushBack(Vector< T >& vector, const T& value)
  {
    if (vector.size == vector.capacity)
    {
      resizeVector(vector);
    }

    vector.data[vector.size] = value;
    vector.size++;
  }

  template< class T >
  void resizeVector(Vector< T >& vector)
  {
    size_t newCapacity = vector.capacity * 2;
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < vector.size; i++)
    {
      newData[i] = vector.data[i];
    }
    delete[] vector.data;
    vector.data = newData;
    vector.capacity = newCapacity;
  }

  template< class T >
  void clearVector(Vector< T >& vector)
  {
    delete[] vector.data;

    vector.data = nullptr;
    vector.size = 0;
    vector.capacity = 0;
  }

  template< class T >
  bool emptyVector(const Vector< T >& vector)
  {
    return vector.size == 0;
  }
}

#endif

