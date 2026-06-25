#ifndef DATABASE_H_
#define DATABASE_H_

#include "person.h"
#include "meeting.h"

namespace smirnova {

    struct Database {
        Person* persons{};
        size_t pCount{};

        Meeting* meetings{};
        size_t mCount{};
    };

    void init(Database& db);
    void destroy(Database& db);

    Person* findPerson(Database& db, size_t id);

    void addPerson(Database& db, const Person& p);
    void addMeeting(Database& db, const Meeting& m);

}

#endif