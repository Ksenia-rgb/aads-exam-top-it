#ifndef SOL_HPP
#define SOL_HPP
#include <string>

namespace petrov
{
  struct Person
  {
    size_t id, h_i, del;
    std::string info;
  };
  struct Meeting
  {
    size_t i1, i2, t, del;
  };
  struct Pvec
  {
    Person* dat;
    size_t s, c;
  };
  struct Mvec
  {
    Meeting* dat;
    size_t s, c;
  };

  size_t cycle(int argc, char** argv);
}

#endif
