#ifndef ARRAY_SORT_HPP
#define ARRAY_SORT_HPP

#include <cstddef>
#include <utility>

#include "array.hpp"

namespace burukov
{

  template< class T, class Less >
  void sortArray(darray< T >& dr, Less less)
  {
    for (size_t i = 1; i < dr.size; ++i)
    {
      T key = std::move(dr.data[i]);
      size_t j = i;
      while (j > 0 && less(key, dr.data[j - 1]))
      {
        dr.data[j] = std::move(dr.data[j - 1]);
        --j;
      }
      dr.data[j] = std::move(key);
    }
  }

}

#endif