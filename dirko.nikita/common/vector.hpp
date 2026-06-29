#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
namespace dirko
{
  template< class T >
  struct Vector
  {
    T *data;
    size_t size;
    size_t cap;
  };
  template< class T >
  void init(Vector< T > &vec)
  {
    vec.data = nullptr;
    vec.size = 0;
    vec.cap = 0;
  }
  template< class T >
  void reserve(Vector< T > &vec, size_t newCap)
  {
    if (vec.cap >= newCap) {
      return;
    }
    T *d = new T[newCap];
    try {
      for (size_t i = 0; i < vec.size; ++i) {
        d[i] = vec.data[i];
      }
    } catch (...) {
      delete[] d;
      throw;
    }
    delete[] vec.data;
    vec.data = d;
    vec.cap = newCap;
  }
  template< class T >
  void add(Vector< T > &vec, const T &val)
  {
    if (vec.size == vec.cap) {
      size_t newCap = (vec.cap == 0 ? 1 : vec.cap * 2);
      reserve(vec, newCap);
    }
    vec.data[vec.size] = val;
    ++vec.size;
  }
  template< class T >
  void clear(Vector< T > &vec)
  {
    delete[] vec.data;
    vec.size = 0;
    vec.cap = 0;
  }
}
#endif
