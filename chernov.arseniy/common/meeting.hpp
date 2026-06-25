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
  chernov::Vector< Meeting > filterMeetingsByPerson(const Vector< Meeting > & meetings, size_t id);
}

#endif
