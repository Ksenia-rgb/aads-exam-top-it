#include "sol.hpp"
#include <iostream>
#include <fstream>

namespace petrov
{
  template<class T>
  void grow_vec(T* data, size_t& c, size_t& s)
  {
    size_t new_c = c * 2;
    T* new_d = new T[new_c];
    for (size_t i = 0; i < s; ++i)
    {
      new_d[i] = data[i];
    }
    delete[] data;
    data = new_d;
    c = new_c;
  }
}