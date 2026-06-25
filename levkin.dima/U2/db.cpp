#include "db.hpp"
#include "db.hpp"
namespace levkin {
  void freeDB(DB& db)
  {
    freeVec(db.persons);
    freeVec(db.meetings);
  }
  bool hasPerson(const DB& db, size_t id)
  {
    for (size_t i = 0; i < db.persons.size; ++i) {
      if (db.persons.data[i].first == id)
        return true;
    }
    return false;
  }
  bool hasDescription(const DB& db, size_t id)
  {
    for (size_t i = 0; i < db.persons.size; ++i) {
      if (db.persons.data[i].first == id) {
        return !db.persons.data[i].second.empty();
      }
    }
    return false;
  }
  void ensurePersonExists(DB& db, size_t id)
  {
    if (!hasPerson(db, id)) {
      Pair p = std::make_pair(id, "");
      pushBack(db.persons, p);
    }
  }
}
