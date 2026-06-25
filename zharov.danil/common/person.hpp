#ifndef PERSON_HPP
#define PERSON_HPP
#include <cstddef>
#include <string>

namespace zharov
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct Meet
  {
    size_t id1;
    size_t id2;
    size_t duration;
  };
}

#endif
