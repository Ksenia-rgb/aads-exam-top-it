#ifndef DATABASE_H_
#define DATABASE_H_

#include "person.h"
#include "meeting.h"

namespace smirnova {

    const size_t MAX_HISTORY = 100;

    struct Database {
        Person* persons{};
        size_t pCount{};

        Meeting* meetings{};
        size_t mCount{};

        Date minDate;
        Date maxDate;
        bool hasDates{false};

        Date rangeMin;
        Date rangeMax;
        bool hasRange{false};

        Date historyMin[MAX_HISTORY];
        Date historyMax[MAX_HISTORY];
        size_t historyCount{0};
    };

    void init(Database& db);
    void destroy(Database& db);

    Person* findPerson(Database& db, size_t id);
    const Person* findPerson(const Database& db, size_t id);  // ДОБАВИТЬ!

    void addPerson(Database& db, const Person& p);
    void addMeeting(Database& db, const Meeting& m);

    void updateRange(Database& db);
    void pushRange(Database& db);
    bool popRange(Database& db);

}

#endif  // DATABASE_H_