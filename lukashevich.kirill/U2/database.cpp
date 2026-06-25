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
