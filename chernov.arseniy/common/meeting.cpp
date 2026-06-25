#include "meeting.hpp"

void chernov::addMeeting(Vector< Meeting > & meetings, size_t from, size_t to, size_t duration, const Date & date)
{
  if (from == to) {
    return;
  }
  Meeting m{from, to, duration, date};
  pushBack(meetings, m);
}
