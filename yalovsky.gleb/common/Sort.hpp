#ifndef SORT_HPP
#define SORT_HPP

#include <cstddef>
#include "Array.hpp"

namespace yalovsky
{
  template< class T >
  void sortArray(Array< T >& arr, bool (*less)(const T&, const T&))
  {
    for (size_t i = 1; i < arr.size; ++i)
    {
      const T key = arr.data[i];
      size_t j = i;
      while (j > 0 && less(key, arr.data[j - 1]))
      {
        arr.data[j] = arr.data[j - 1];
        --j;
      }
      arr.data[j] = key;
    }
  }
}

#endif
