#include "io.hpp"

#include <fstream>
#include <iostream>

namespace
{
  bool findPerson(const petrov::DataBase& db, std::size_t id)
  {
    for (std::size_t i = 0; i < db.persons.size; ++i)
    {
      if (db.persons.data[i].id == id)
      {
        return true;
      }
    }
    return false;
  }

  void ensurePersonExists(petrov::DataBase& db, std::size_t id)
  {
    if (!findPerson(db, id))
    {
      petrov::Person person = {};
      person.id = id;
      person.hasInfo = false;
      petrov::detail::pushBackArray(db.persons, person);
    }
  }
}

bool petrov::readPersonsFromFile(const std::string& filename, DataBase& db)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    return false;
  }
  std::size_t id = 0;
  std::string info = "";
  while (file >> id)
  {
    std::getline(file, info);
    if (info.size() == 0)
    {
      continue;
    }
    if (info[0] == ' ')
    {
      info.erase(0, 1);
    }
    Person person = {};
    person.id = id;
    person.info = info;
    person.hasInfo = true;
    detail::pushBackArray(db.persons, person);
  }
  return true;
}

int petrov::readMeetingsFromFile(const std::string& filename, DataBase& db)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    return 2;
  }
  std::size_t first = 0;
  std::size_t second = 0;
  std::size_t time = 0;
  while (file >> first >> second >> time)
  {
    if (first == second)
    {
      continue;
    }
    ensurePersonExists(db, first);
    ensurePersonExists(db, second);
    Meeting meeting = {};
    meeting.first = first;
    meeting.second = second;
    meeting.time = time;
    detail::pushBackArray(db.meetings, meeting);
  }
  if (!file.eof())
  {
    return 3;
  }
  return 0;
}
