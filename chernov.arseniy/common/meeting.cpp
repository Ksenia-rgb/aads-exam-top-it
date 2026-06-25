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

size_t chernov::detail::getOther(const Meeting & m, size_t id)
{
  return (m.from == id) ? m.to : m.from;
}

bool chernov::detail::shouldSwap(const Meeting & a, const Meeting & b, size_t id)
{
  size_t otherA = detail::getOther(a, id);
  size_t otherB = detail::getOther(b, id);
  if (otherA != otherB) {
    return otherA > otherB;
  }
  return a.duration > b.duration;
}

void chernov::sortMeetingsForOutput(Vector< Meeting > & meetings, size_t id)
{
  size_t n = meetings.size;
  for (size_t i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (size_t j = 0; j < n - i - 1; ++j) {
      if (detail::shouldSwap(meetings.data[j], meetings.data[j + 1], id)) {
        Meeting temp = meetings.data[j];
        meetings.data[j] = meetings.data[j + 1];
        meetings.data[j + 1] = temp;
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }
}

void chernov::applyDeanon(Vector< Meeting > & meetings, size_t anonId, size_t id)
{
  Vector< Meeting > newMeetings;
  init(newMeetings);

  try {
    for (size_t i = 0; i < meetings.size; ++i) {
      Meeting m = meetings.data[i];
      if (m.from == anonId) {
        m.from = id;
      }
      if (m.to == anonId) {
        m.to = id;
      }
      if (m.from != m.to) {
        pushBack(newMeetings, m);
      }
    }
  } catch (...) {
    destroy(newMeetings);
    throw;
  }

  destroy(meetings);
  meetings.data = newMeetings.data;
  meetings.size = newMeetings.size;
  meetings.capacity = newMeetings.capacity;

  init(newMeetings);
}
