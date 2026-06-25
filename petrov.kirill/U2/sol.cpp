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

  size_t cycle(int argc, char** argv)
  {
    if (argc < 2 || argc > 3)
    {
      std::cerr << "too much\n";
      return 1;
    }
    std::string inf = "", df = "";
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if (!arg.rfind("in:", 0)) {
        if (!inf.empty()) {
          std::cerr << "dubl\n";
          return 1;
        }
        inf = arg.substr(3);
      } else if (!arg.rfind("data:", 0)) {
        if (!df.empty()) {
          std::cerr << "dubl\n";
          return 1;
        }
        df = arg.substr(5);
      } else {
        std::cerr << "inval\n";
        return 1;
      }
    }
    if (df.empty())
    {
      std::cerr << "err\n";
      return 1;
    }
    Pvec ps = {nullptr, 0, 0};
    Mvec ms = {nullptr, 0, 0};
  }
}
