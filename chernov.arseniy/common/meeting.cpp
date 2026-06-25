#include "meeting.hpp"

void chernov::addMeeting(Vector< Meeting > & meetings, size_t from, size_t to, size_t duration, const Date & date)
{
  if (from == to) {
    return;
  }
  Meeting m{from, to, duration, date};
  pushBack(meetings, m);
}

chernov::Vector< chernov::Meeting > chernov::filterMeetingsByPerson(const Vector< Meeting > & meetings, size_t id)
{
  Vector< Meeting > result;
  init(result);
  try {
    for (size_t i = 0; i < meetings.size; ++i) {
      const Meeting & m = meetings.data[i];
      if (m.from == id || m.to == id) {
        pushBack(result, m);
      }
    }
  } catch (...) {
    destroy(result);
    throw;
  }
  return result;
}
