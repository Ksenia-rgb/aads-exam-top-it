#ifndef MEETING_HPP
#define MEETING_HPP

#include <cstddef>
#include <iosfwd>
#include "dynarray.hpp"

namespace shigarev {
  struct Meeting {
    size_t id1;
    size_t id2;
    size_t duration;
  };

  bool readMeetings(std::istream& in,
      DynArray< Meeting >& meetings);
}

#endif

