#ifndef MEETING_HPP
#define MEETING_HPP

#include <cstddef>
#include "date.hpp"
#include "vector.hpp"

namespace chernov {

  struct Meeting {
    size_t from;
    size_t to;
    size_t duration;
    Date date;
  };

  void addMeeting(Vector< Meeting > & meetings, size_t from, size_t to, size_t duration, const Date & date);
  Vector< Meeting > filterMeetingsByPerson(const Vector< Meeting > & meetings, size_t id);
  Vector< size_t > getNeighbors(const Vector< Meeting > & meetings, size_t id);
  void sortMeetingsForOutput(Vector< Meeting > & meetings, size_t id);

  namespace detail {
    size_t getOther(const Meeting & m, size_t id);
    bool shouldSwap(const Meeting & a, const Meeting & b, size_t id);
  }
}

#endif
