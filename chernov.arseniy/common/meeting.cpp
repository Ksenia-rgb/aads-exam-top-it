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

chernov::Vector< size_t > chernov::getNeighbors(const Vector< Meeting > & meetings, size_t id)
{
  Vector< Meeting > filtered = filterMeetingsByPerson(meetings, id);
  Vector< size_t > neighbors;
  init(neighbors);

  try {
    for (size_t i = 0; i < filtered.size; ++i) {
      const Meeting & m = filtered.data[i];
      size_t other = (m.from == id) ? m.to : m.from;
      bool found = false;
      for (size_t j = 0; j < neighbors.size; ++j) {
        if (neighbors.data[j] == other) {
          found = true;
          break;
        }
      }
      if (!found) {
        pushBack(neighbors, other);
      }
    }
  } catch (...) {
    destroy(neighbors);
    destroy(filtered);
    throw;
  }

  destroy(filtered);
  return neighbors;
}
