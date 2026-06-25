#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

namespace lukashevich
{
  template< typename T >
  struct Array
  {
    T* data_;
    size_t size_;
    size_t capacity_;
  };
}

#endif
