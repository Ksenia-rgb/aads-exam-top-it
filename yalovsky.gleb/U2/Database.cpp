#include "Database.hpp"

#include <istream>
#include <string>
#include "../common/Parse.hpp"

namespace yalovsky
{
  Database makeDatabase()
  {
    Database result{makeArray< Person >(), makeArray< Meeting >()};
    return result;
  }

  void freeDatabase(Database& db)
  {
    freeArray(db.persons);
    freeArray(db.meetings);
  }

  bool findPerson(const Database& db, size_t id, size_t& index)
  {
    for (size_t i = 0; i < db.persons.size; ++i)
    {
      if (db.persons.data[i].id == id)
      {
        index = i;
        return true;
      }
    }
    return false;
  }

  bool hasDescription(const Database& db, size_t id)
  {
    size_t index = 0;
    if (!findPerson(db, id, index))
    {
      return false;
    }
    return !db.persons.data[index].info.empty();
  }

  void ensurePerson(Database& db, size_t id)
  {
    size_t index = 0;
    if (findPerson(db, id, index))
    {
      return;
    }
    const Person person{id, std::string()};
    pushBack(db.persons, person);
  }

  void loadPersons(std::istream& in, Database& db)
  {
    std::string line;
    while (std::getline(in, line))
    {
      size_t pos = 0;
      size_t id = 0;
      if (!readNumber(line, pos, id))
      {
        continue;
      }
      skipSpaces(line, pos);
      if (pos == line.size())
      {
        continue;
      }
      const std::string info = line.substr(pos);
      size_t index = 0;
      if (findPerson(db, id, index))
      {
        continue;
      }
      const Person person{id, info};
      pushBack(db.persons, person);
    }
  }

  bool loadMeetings(std::istream& in, Database& db)
  {
    size_t a = 0;
    while (in >> a)
    {
      size_t b = 0;
      size_t duration = 0;
      if (!(in >> b >> duration))
      {
        return false;
      }
      if (a == b)
      {
        continue;
      }
      ensurePerson(db, a);
      ensurePerson(db, b);
      Meeting meeting{a < b ? a : b, a < b ? b : a, duration};
      pushBack(db.meetings, meeting);
    }
    return in.eof();
  }

  bool deanon(Database& db, size_t anonId, size_t id)
  {
    if (hasDescription(db, anonId) || !hasDescription(db, id))
    {
      return false;
    }
    size_t anonIndex = 0;
    if (!findPerson(db, anonId, anonIndex))
    {
      return false;
    }
    size_t i = 0;
    while (i < db.meetings.size)
    {
      Meeting& meeting = db.meetings.data[i];
      if (meeting.a == anonId)
      {
        meeting.a = id;
      }
      if (meeting.b == anonId)
      {
        meeting.b = id;
      }
      if (meeting.a == meeting.b)
      {
        removeAt(db.meetings, i);
        continue;
      }
      if (meeting.a > meeting.b)
      {
        const size_t temp = meeting.a;
        meeting.a = meeting.b;
        meeting.b = temp;
      }
      ++i;
    }
    removeAt(db.persons, anonIndex);
    return true;
  }
}
