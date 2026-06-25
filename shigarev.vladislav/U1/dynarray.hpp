ifndef DYNARRAY_HPP
#define DYNARRAY_HPP
 
#include <cstddef>
#include <utility>
 
namespace shigarev {
  template< class T >
  struct DynArray {
    T* data_;
    size_t size_;
    size_t capacity_;
  };
 
  template< class T >
  DynArray< T > createDynArray(size_t capacity)
  {
    DynArray< T > result = {nullptr, 0, 0};
    if (capacity > 0) {
      result.data_ = new T[capacity];
      result.capacity_ = capacity;
    }
    return result;
  }
}
