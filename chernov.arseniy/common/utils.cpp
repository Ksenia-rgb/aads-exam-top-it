#include "utils.hpp"

void chernov::addUniqueId(Vector< size_t > & allIds, size_t id)
{
  for (size_t i = 0; i < allIds.size; ++i) {
    if (allIds.data[i] == id) {
      return;
    }
  }
  pushBack(allIds, id);
}

bool chernov::hasId(const Vector< size_t > & allIds, size_t id)
{
  for (size_t i = 0; i < allIds.size; ++i) {
    if (allIds.data[i] == id) {
      return true;
    }
  }
  return false;
}

void chernov::rebuildAllIds(Vector< size_t > & allIds,
  const Vector< Person > & persons,
  const Vector< Meeting > & meetings)
{
  Vector< size_t > newAllIds;
  init(newAllIds);

  try {
    for (size_t i = 0; i < persons.size; ++i) {
      addUniqueId(newAllIds, persons.data[i].id);
    }
    for (size_t i = 0; i < meetings.size; ++i) {
      addUniqueId(newAllIds, meetings.data[i].from);
      addUniqueId(newAllIds, meetings.data[i].to);
    }
  } catch (...) {
    destroy(newAllIds);
    throw;
  }

  destroy(allIds);
  allIds.data = newAllIds.data;
  allIds.size = newAllIds.size;
  allIds.capacity = newAllIds.capacity;

  init(newAllIds);
}

size_t chernov::otherId(const chernov::Meeting & m, size_t id)
{
  return (m.from == id) ? m.to : m.from;
}

void chernov::printMeetingList(chernov::Vector< chernov::Meeting > & meetings, size_t id)
{
  chernov::sortMeetingsForOutput(meetings, id);
  for (size_t i = 0; i < meetings.size; ++i) {
    std::cout << otherId(meetings.data[i], id) << ' ' << meetings.data[i].duration << '\n';
  }
}

bool chernov::parseSize(const std::string & text, size_t & value)
{
  if (text.empty())
    return false;
  for (size_t i = 0; i < text.size(); ++i) {
    if (text[i] < '0' || text[i] > '9')
      return false;
  }
  size_t pos;
  try {
    value = std::stoull(text, &pos);
  } catch (...) {
    return false;
  }
  return pos == text.size();
}

bool chernov::hasIdInAll(const chernov::Vector< size_t > & allIds, size_t id)
{
  return chernov::hasId(allIds, id);
}
