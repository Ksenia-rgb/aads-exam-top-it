#include "utils.hpp"

namespace levkin {
  Pair* reallocate(Vec& v)
  {
    size_t nw_cap = 0;
    if (v.cap == 0) {
      nw_cap = 1;
    } else {
      nw_cap = 2 * v.cap;
    }
    Pair* nw = new Pair[nw_cap];
    v.cap = nw_cap;
    for (size_t i = 0; i < v.size; i++) {
      nw[i] = v.data[i];
    }
    if (v.data != nullptr) {
      delete[] v.data;
    }
    v.data = nw;
    return nw;
  }

}
