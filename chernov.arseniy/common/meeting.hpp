#ifndef MEETING_HPP
#define MEETING_HPP

#include <cstddef>
#include "date.hpp"

namespace chernov {

  struct Meeting {
    size_t from;
    size_t to;
    size_t duration;
    Date date;
  };

}

#endif
