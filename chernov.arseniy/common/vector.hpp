#include <cstddef>

namespace chernov {

  template< class T >
  struct Vector {
    T * data;
    size_t size;
    size_t capacity;
  };

  template< class T >
  void init(Vector< T > & v);

  template< class T >
  void destroy(Vector< T > & v);

  template< class T >
  void reserve(Vector< T > & v, size_t newCap);

  template< class T >
  void pushBack(Vector< T > & v, const T & value);

}

template< typename T >
void chernov::init(Vector< T > & v)
{
  v.data = nullptr;
  v.size = 0;
  v.capacity = 0;
}

template< typename T >
void chernov::destroy(Vector< T > & v)
{
  if (v.data) {
    delete[] v.data;
  }
  init(v);
}

template< class T >
void chernov::reserve(Vector< T > & v, size_t newCap)
{
  if (newCap <= v.capacity) {
    return;
  }
  T * newData = new T[newCap];
  try {
    for (size_t i = 0; i < v.size; ++i) {
      newData[i] = v.data[i];
    }
  } catch (...) {
    delete[] newData;
    throw;
  }
  delete[] v.data;
  v.data = newData;
  v.capacity = newCap;
}

template< class T >
void chernov::pushBack(Vector< T > & v, const T & value)
{
  if (v.size == v.capacity) {
    reserve(v, v.capacity == 0 ? 1 : v.capacity * 2);
  }
  v.data[v.size] = value;
  ++v.size;
}
