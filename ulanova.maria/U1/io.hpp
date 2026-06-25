#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <iostream>

namespace ulanova
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  template < class T >
  struct Array
  {
    T * data;
    size_t size;
    size_t capacity;
  };

  template < class T >
  Array< T > mArray()
  {
    return Array< T >{nullptr, 0, 0};
  }

  template < class T >
  void clear(Array< T > & arr)
  {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
  }

  template < class T >
  void pushBack(Array< T > & arr, const T & val)
  {
    if (arr.size == arr.capacity)
    {
      const size_t newCap = arr.capacity == 0 ? 4 : arr.capacity * 2;
      T * newData = new T[newCap];
      for (size_t i = 0; i < arr.size; ++i)
      {
        newData[i] = arr.data[i];
      }
      delete[] arr.data;
      arr.data = newData;
      arr.capacity = newCap;
    }
    arr.data[arr.size++] = val;
  }

  bool containsId(const Array< Person > & arr, size_t id);
  void printPersons(const Array< Person > & arr, std::ostream & out);
}

#endif
