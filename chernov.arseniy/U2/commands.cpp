#include "commands.hpp"
#include <sort.hpp>
#include <utils.hpp>

void chernov::printAnons(const Vector< size_t > & allIds, const Vector< Person > & persons)
{
  Vector< size_t > idsCopy;
  init(idsCopy);

  try {
    for (size_t i = 0; i < allIds.size; ++i) {
      pushBack(idsCopy, allIds.data[i]);
    }

    bubbleSort(idsCopy);

    for (size_t i = 0; i < idsCopy.size; ++i) {
      size_t id = idsCopy.data[i];
      if (findById(persons, id) == persons.size) {
        std::cout << id << '\n';
      }
    }
  } catch (...) {
    destroy(idsCopy);
    throw;
  }

  destroy(idsCopy);
}

bool chernov::processDeanon(Vector< Person > & persons,
  Vector< Meeting > & meetings,
  Vector< size_t > & allIds,
  size_t anonId,
  size_t id)
{
  bool anonExists = false;
  for (size_t i = 0; i < allIds.size; ++i) {
    if (allIds.data[i] == anonId) {
      anonExists = true;
      break;
    }
  }
  if (!anonExists) {
    return false;
  }

  if (findById(persons, anonId) != persons.size) {
    return false;
  }

  if (findById(persons, id) == persons.size) {
    return false;
  }

  applyDeanon(meetings, anonId, id);

  rebuildAllIds(allIds, persons, meetings);

  return true;
}

bool chernov::processRedesc(Vector< Person > & persons,
  Vector< size_t > & allIds,
  size_t id,
  const std::string & description)
{
  bool existsInAllIds = false;
  for (size_t i = 0; i < allIds.size; ++i) {
    if (allIds.data[i] == id) {
      existsInAllIds = true;
      break;
    }
  }
  if (!existsInAllIds) {
    return false;
  }

  size_t idx = findById(persons, id);
  if (idx != persons.size) {
    persons.data[idx].info = description;
  } else {
    Person p{id, description};
    pushBack(persons, p);
  }
  return true;
}
