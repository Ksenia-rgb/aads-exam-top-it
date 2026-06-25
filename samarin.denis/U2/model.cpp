#include "model.hpp"

#include <string>

namespace {
  bool comesBeforeById(const samarin::Person & left, const samarin::Person & right)
  {
    return left.id < right.id;
  }
}

bool samarin::insertPerson(Dataset & data, std::size_t id, bool named,
    const std::string & description)
{
  if (findPerson(data, id) != nullptr) {
    return false;
  }
  const Person person{ id, named, description };
  detail::insertSorted(data.persons, person, comesBeforeById);
  return true;
}

samarin::Person * samarin::findPerson(Dataset & data, std::size_t id)
{
  const auto hasId = [id](const Person & person)
  {
    return person.id == id;
  };
  return detail::findValue(data.persons, hasId);
}

void samarin::addMeeting(Dataset & data, std::size_t first, std::size_t second,
    std::size_t duration)
{
  if (first == second) {
    return;
  }
  insertPerson(data, first, false, "");
  insertPerson(data, second, false, "");
  const Meeting meeting{ first, second, duration };
  detail::pushBack(data.meetings, meeting);
}

void samarin::clearDataset(Dataset & data)
{
  detail::clear(data.persons);
  detail::clear(data.meetings);
}
