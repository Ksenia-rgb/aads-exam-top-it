#include "database.hpp"
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

namespace hvostov {
  void initDatabase(Database& db)
  {
    db.persons = nullptr;
    db.personsCount = 0;
    db.personsCapacity = 0;
    db.meetings = nullptr;
    db.meetingsCount = 0;
    db.meetingsCapacity = 0;
  }

  void freeDatabase(Database& db)
  {
    delete[] db.persons;
    delete[] db.meetings;
    initDatabase(db);
  }

  void addPerson(Database& db, const Person& p)
  {
    // Проверяем, существует ли уже такое лицо
    for (size_t i = 0; i < db.personsCount; ++i) {
      if (db.persons[i].id == p.id) {
        return;
      }
    }

    // Расширяем массив при необходимости
    if (db.personsCount >= db.personsCapacity) {
      size_t newCapacity = db.personsCapacity == 0 ? 8 : db.personsCapacity * 2;
      Person* newPersons = new Person[newCapacity];
      for (size_t i = 0; i < db.personsCount; ++i) {
        newPersons[i] = db.persons[i];
      }
      delete[] db.persons;
      db.persons = newPersons;
      db.personsCapacity = newCapacity;
    }

    db.persons[db.personsCount++] = p;
  }

  void addMeeting(Database& db, const Meeting& m)
  {
    // Расширяем массив при необходимости
    if (db.meetingsCount >= db.meetingsCapacity) {
      size_t newCapacity = db.meetingsCapacity == 0 ? 8 : db.meetingsCapacity * 2;
      Meeting* newMeetings = new Meeting[newCapacity];
      for (size_t i = 0; i < db.meetingsCount; ++i) {
        newMeetings[i] = db.meetings[i];
      }
      delete[] db.meetings;
      db.meetings = newMeetings;
      db.meetingsCapacity = newCapacity;
    }

    db.meetings[db.meetingsCount++] = m;

    // Добавляем участников, если их нет
    Person p1 = {m.id1, "", false};
    Person p2 = {m.id2, "", false};
    addPerson(db, p1);
    addPerson(db, p2);
  }

  const Person* findPerson(const Database& db, size_t id)
  {
    for (size_t i = 0; i < db.personsCount; ++i) {
      if (db.persons[i].id == id) {
        return &db.persons[i];
      }
    }
    return nullptr;
  }

  bool hasDescription(const Database& db, size_t id)
  {
    const Person* p = findPerson(db, id);
    return p != nullptr && p->hasDescription;
  }

  void anons(const Database& db, std::ostream& out)
  {
    std::vector< size_t > anonIds;
    for (size_t i = 0; i < db.personsCount; ++i) {
      if (!db.persons[i].hasDescription) {
        anonIds.push_back(db.persons[i].id);
      }
    }
    std::sort(anonIds.begin(), anonIds.end());
    for (size_t id : anonIds) {
      out << id << '\n';
    }
  }

  bool deanon(Database& db, size_t anonId, size_t realId)
  {
    const Person* anon = findPerson(db, anonId);
    const Person* real = findPerson(db, realId);

    if (!anon || !real)
      return false;
    if (anon->hasDescription || !real->hasDescription)
      return false;

    // Переносим встречи
    for (size_t i = 0; i < db.meetingsCount; ++i) {
      if (db.meetings[i].id1 == anonId)
        db.meetings[i].id1 = realId;
      if (db.meetings[i].id2 == anonId)
        db.meetings[i].id2 = realId;
    }

    // Удаляем встречи с самим собой
    size_t writeIdx = 0;
    for (size_t i = 0; i < db.meetingsCount; ++i) {
      if (db.meetings[i].id1 != db.meetings[i].id2) {
        db.meetings[writeIdx++] = db.meetings[i];
      }
    }
    db.meetingsCount = writeIdx;

    // Удаляем anonId из persons
    writeIdx = 0;
    for (size_t i = 0; i < db.personsCount; ++i) {
      if (db.persons[i].id != anonId) {
        db.persons[writeIdx++] = db.persons[i];
      }
    }
    db.personsCount = writeIdx;

    return true;
  }

  void desc(const Database& db, size_t id, std::ostream& out)
  {
    const Person* p = findPerson(db, id);
    if (!p) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (!p->hasDescription) {
      out << "<ANON>\n";
    } else {
      out << p->info << '\n';
    }
  }

  bool redesc(Database& db, size_t id, const std::string& desc)
  {
    Person* p = const_cast< Person* >(findPerson(db, id));
    if (!p)
      return false;
    p->info = desc;
    p->hasDescription = true;
    return true;
  }

  void meets(const Database& db, size_t id, std::ostream& out)
  {
    if (!findPerson(db, id)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    std::vector< std::pair< size_t, size_t > > result;
    for (size_t i = 0; i < db.meetingsCount; ++i) {
      if (db.meetings[i].id1 == id) {
        result.push_back({db.meetings[i].id2, db.meetings[i].duration});
      } else if (db.meetings[i].id2 == id) {
        result.push_back({db.meetings[i].id1, db.meetings[i].duration});
      }
    }

    std::sort(result.begin(), result.end());
    for (const auto& r : result) {
      out << r.first << ' ' << r.second << '\n';
    }
  }

  void commons(const Database& db, size_t id1, size_t id2, std::ostream& out)
  {
    if (!findPerson(db, id1) || !findPerson(db, id2)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    std::set< size_t > meets1, meets2;
    for (size_t i = 0; i < db.meetingsCount; ++i) {
      if (db.meetings[i].id1 == id1)
        meets1.insert(db.meetings[i].id2);
      else if (db.meetings[i].id2 == id1)
        meets1.insert(db.meetings[i].id1);
      if (db.meetings[i].id1 == id2)
        meets2.insert(db.meetings[i].id2);
      else if (db.meetings[i].id2 == id2)
        meets2.insert(db.meetings[i].id1);
    }

    std::vector< size_t > common;
    for (size_t id : meets1) {
      if (meets2.find(id) != meets2.end()) {
        common.push_back(id);
      }
    }

    std::sort(common.begin(), common.end());
    for (size_t id : common) {
      out << id << '\n';
    }
  }

  void less(const Database& db, size_t time, size_t id, std::ostream& out)
  {
    if (!findPerson(db, id)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    std::vector< std::pair< size_t, size_t > > result;
    for (size_t i = 0; i < db.meetingsCount; ++i) {
      if (db.meetings[i].duration < time) {
        if (db.meetings[i].id1 == id) {
          result.push_back({db.meetings[i].id2, db.meetings[i].duration});
        } else if (db.meetings[i].id2 == id) {
          result.push_back({db.meetings[i].id1, db.meetings[i].duration});
        }
      }
    }

    std::sort(result.begin(), result.end());
    for (const auto& r : result) {
      out << r.first << ' ' << r.second << '\n';
    }
  }

  void greater(const Database& db, size_t time, size_t id, std::ostream& out)
  {
    if (!findPerson(db, id)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    std::vector< std::pair< size_t, size_t > > result;
    for (size_t i = 0; i < db.meetingsCount; ++i) {
      if (db.meetings[i].duration > time) {
        if (db.meetings[i].id1 == id) {
          result.push_back({db.meetings[i].id2, db.meetings[i].duration});
        } else if (db.meetings[i].id2 == id) {
          result.push_back({db.meetings[i].id1, db.meetings[i].duration});
        }
      }
    }

    std::sort(result.begin(), result.end());
    for (const auto& r : result) {
      out << r.first << ' ' << r.second << '\n';
    }
  }

  void outPersons(const Database& db, const std::string& filename)
  {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
      std::cerr << "Error: cannot open output file\n";
      return;
    }

    for (size_t i = 0; i < db.personsCount; ++i) {
      if (db.persons[i].hasDescription) {
        outFile << db.persons[i] << '\n';
      }
    }
  }
}
