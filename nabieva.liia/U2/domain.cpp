#include "domain.hpp"
#include "dynamic-array.hpp"

namespace nabieva
{
  void init(Database& database)
  {
    init(database.persons);
    init(database.meetings);
  }

  void clear(Database& database)
  {
    clear(database.meetings);
    clear(database.persons);
  }

  int findPersonIndex(const Database& database, int id)
  {
    for (std::size_t i = 0; i < database.persons.size; ++i)
    {
      if (database.persons.data[i].id == id)
      {
        return static_cast<int>(i);
      }
    }
    return -1;
  }

  Person& getOrCreatePerson(Database& database, int id)
  {
    const int index = findPersonIndex(database, id);
    if (index != -1)
    {
      return database.persons.data[index];
    }

    pushBack(database.persons, makeAnonPerson(id));
    return database.persons.data[database.persons.size - 1];
  }

  void setDescription(Database& database, int id, const std::string& description)
  {
    Person& person = getOrCreatePerson(database, id);
    person.description = description;
    person.hasDescription = true;
  }
}