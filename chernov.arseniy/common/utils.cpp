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
