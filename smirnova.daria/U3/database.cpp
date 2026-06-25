#include "database.h"

namespace smirnova {

    void init(Database& db) {
        db.persons = nullptr;
        db.meetings = nullptr;
        db.pCount = 0;
        db.mCount = 0;
        db.hasDates = false;
        db.hasRange = false;
        db.historyCount = 0;
    }

    void destroy(Database& db) {
        delete[] db.persons;
        delete[] db.meetings;
    }

    Person* findPerson(Database& db, size_t id) {
        for (size_t i = 0; i < db.pCount; ++i) {
            if (db.persons[i].id == id) {
                return &db.persons[i];
            }
        }
        return nullptr;
    }

    // ДОБАВИТЬ константную версию!
    const Person* findPerson(const Database& db, size_t id) {
        for (size_t i = 0; i < db.pCount; ++i) {
            if (db.persons[i].id == id) {
                return &db.persons[i];
            }
        }
        return nullptr;
    }

    void addPerson(Database& db, const Person& p) {
        if (findPerson(db, p.id) != nullptr) {
            return;
        }

        Person* tmp = new Person[db.pCount + 1];
        for (size_t i = 0; i < db.pCount; ++i) {
            tmp[i] = db.persons[i];
        }

        tmp[db.pCount] = p;
        ++db.pCount;

        delete[] db.persons;
        db.persons = tmp;
    }

    void addMeeting(Database& db, const Meeting& m) {
        Meeting* tmp = new Meeting[db.mCount + 1];
        for (size_t i = 0; i < db.mCount; ++i) {
            tmp[i] = db.meetings[i];
        }

        tmp[db.mCount] = m;
        ++db.mCount;

        delete[] db.meetings;
        db.meetings = tmp;

        if (!db.hasDates) {
            db.minDate = m.date;
            db.maxDate = m.date;
            db.hasDates = true;
        } else {
            if (m.date < db.minDate) {
                db.minDate = m.date;
            }
            if (m.date > db.maxDate) {
                db.maxDate = m.date;
            }
        }
    }

    void updateRange(Database& db) {
        if (!db.hasDates) {
            db.hasRange = false;
            return;
        }

        db.hasRange = true;
        db.rangeMin = db.minDate;
        db.rangeMax = db.maxDate;
    }

    void pushRange(Database& db) {
        if (!db.hasRange) {
            return;
        }

        if (db.historyCount < MAX_HISTORY) {
            db.historyMin[db.historyCount] = db.rangeMin;
            db.historyMax[db.historyCount] = db.rangeMax;
            ++db.historyCount;
        }
    }

    bool popRange(Database& db) {
        if (db.historyCount == 0) {
            return false;
        }

        --db.historyCount;
        db.rangeMin = db.historyMin[db.historyCount];
        db.rangeMax = db.historyMax[db.historyCount];
        db.hasRange = true;
        return true;
    }

}  // namespace smirnova