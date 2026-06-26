#include "database.h"

namespace smirnova {

    void init(Database& db) {
        db.persons = nullptr;
        db.meetings = nullptr;
        db.pCount = 0;
        db.mCount = 0;
    }

    void destroy(Database& db) {
        delete[] db.persons;
        delete[] db.meetings;
    }

    Person* findPerson(Database& db, size_t id) {
        for (size_t i = 0; i < db.pCount; ++i)
            if (db.persons[i].id == id)
                return &db.persons[i];
        return nullptr;
    }

    void addPerson(Database& db, const Person& p) {
        Person* tmp = new Person[db.pCount + 1];
        for (size_t i = 0; i < db.pCount; ++i)
            tmp[i] = db.persons[i];

        tmp[db.pCount++] = p;

        delete[] db.persons;
        db.persons = tmp;
    }

    void addMeeting(Database& db, const Meeting& m) {
        Meeting* tmp = new Meeting[db.mCount + 1];
        for (size_t i = 0; i < db.mCount; ++i)
            tmp[i] = db.meetings[i];

        tmp[db.mCount++] = m;

        delete[] db.meetings;
        db.meetings = tmp;
    }

}