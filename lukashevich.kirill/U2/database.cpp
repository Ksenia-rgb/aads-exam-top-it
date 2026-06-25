#include "database.hpp"

void lukashevich::initDatabase(Database& database) noexcept
{
  initArray(database.persons);
  initArray(database.meetings);
}

void lukashevich::destroyDatabase(Database& database) noexcept
{
  destroyArray(database.meetings);
  destroyArray(database.persons);
}

void lukashevich::addAnonPerson(Database& database, size_t id)
{
  if (hasPerson(database.persons, id)) {
    return;
  }

  Person person;
  person.id = id;
  person.info.clear();
  person.hasInfo = false;

  pushBack(database.persons, person);
}

bool lukashevich::addDescribedPerson(Database& database,
  size_t id, const std::string& info)
{
  if (hasPerson(database.persons, id)) {
    return false;
  }

  Person person;
  person.id = id;
  person.info = info;
  person.hasInfo = true;

  pushBack(database.persons, person);
  return true;
}

void lukashevich::addMeeting(Database& database, size_t first,
  size_t second, size_t time)
{
  if (first == second) {
    return;
  }

  addAnonPerson(database, first);
  addAnonPerson(database, second);

  Meeting meeting;
  meeting.first = first;
  meeting.second = second;
  meeting.time = time;

  pushBack(database.meetings, meeting);
}

bool lukashevich::hasMeetingWith(const Database& database, size_t id, size_t other)
{}

bool lukashevich::pushUniqueId(Array< size_t >& ids, size_t id)
{}

void lukashevich::sortIds(Array< size_t >& ids)
{}

void lukashevich::sortMeetingViews(Array< MeetingView >& views)
{}
