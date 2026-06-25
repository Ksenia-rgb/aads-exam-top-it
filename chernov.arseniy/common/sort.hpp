#ifndef SORT_HPP
#define SORT_HPP

#include "vector.hpp"

namespace chernov {

  template< class T >
  void bubbleSort(Vector< T > & v)
  {
    size_t n = v.size;
    for (size_t i = 0; i < n - 1; ++i) {
      bool swapped = false;
      for (size_t j = 0; j < n - i - 1; ++j) {
        if (v.data[j] > v.data[j + 1]) {
          T temp = v.data[j];
          v.data[j] = v.data[j + 1];
          v.data[j + 1] = temp;
          swapped = true;
        }
      }
      if (!swapped) {
        break;
      }
    }
  }

}

#endif
