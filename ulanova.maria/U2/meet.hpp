#ifndef MEET_HPP
#define MEET_HPP

#include "../common/io.hpp"

#include <iostream>

namespace ulanova
{
  struct Meet
  {
    size_t id1;
    size_t id2;
    size_t duration;
  };

  Array< Meet > readMeets(std::istream & in);
}

#endif
