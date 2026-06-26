#include "commands.hpp"
#include <fstream>
#include <iostream>
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

void chernov::printMeets(const Vector< Meeting > & meetings, size_t id)
{
  Vector< Meeting > filtered = filterMeetingsByPerson(meetings, id);
  try {
    printMeetingList(filtered, id);
  } catch (...) {
    destroy(filtered);
    throw;
  }
  destroy(filtered);
}

void chernov::printDurationFiltered(const Vector< Meeting > & meetings, size_t id, size_t duration, bool greater)
{
  Vector< Meeting > filtered;
  init(filtered);

  try {
    for (size_t i = 0; i < meetings.size; ++i) {
      const Meeting & m = meetings.data[i];
      bool matchesPerson = (m.from == id || m.to == id);
      bool matchesDuration = greater ? (m.duration > duration) : (m.duration < duration);
      if (matchesPerson && matchesDuration) {
        pushBack(filtered, m);
      }
    }
    printMeetingList(filtered, id);
  } catch (...) {
    destroy(filtered);
    throw;
  }
  destroy(filtered);
}

void chernov::printCommons(const Vector< Meeting > & meetings, size_t first, size_t second)
{
  Vector< size_t > neighbors = getNeighbors(meetings, first);
  Vector< size_t > common;
  init(common);

  try {
    for (size_t i = 0; i < neighbors.size; ++i) {
      size_t candidate = neighbors.data[i];
      bool found = false;
      for (size_t j = 0; j < meetings.size; ++j) {
        const Meeting & m = meetings.data[j];
        if ((m.from == second && m.to == candidate) || (m.to == second && m.from == candidate)) {
          found = true;
          break;
        }
      }
      if (found) {
        addUniqueId(common, candidate);
      }
    }

    bubbleSort(common);
    for (size_t i = 0; i < common.size; ++i) {
      std::cout << common.data[i] << '\n';
    }
  } catch (...) {
    destroy(neighbors);
    destroy(common);
    throw;
  }

  destroy(neighbors);
  destroy(common);
}

bool chernov::writePersons(const std::string & filename, const Vector< Person > & persons)
{
  std::ofstream fout(filename);
  if (!fout.is_open()) {
    return false;
  }
  for (size_t i = 0; i < persons.size; ++i) {
    fout << persons.data[i].id << ' ' << persons.data[i].info << '\n';
  }
  return true;
}
