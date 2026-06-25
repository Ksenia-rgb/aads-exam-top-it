#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cstddef>
#include <string>
#include <iosfwd>
#include "../common/Array.hpp"

namespace yalovsky
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct Meeting
  {
    size_t a;
    size_t b;
    size_t duration;
  };

  struct Database
  {
    Array< Person > persons;
    Array< Meeting > meetings;
  };

  Database makeDatabase();
  void freeDatabase(Database& db);

  bool findPerson(const Database& db, size_t id, size_t& index);
  bool hasDescription(const Database& db, size_t id);
  void ensurePerson(Database& db, size_t id);

  void loadPersons(std::istream& in, Database& db);
  bool loadMeetings(std::istream& in, Database& db);

  bool deanon(Database& db, size_t anonId, size_t id);
}

#endif
