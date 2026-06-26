#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "database.h"

namespace smirnova {

    void anons(Database& db);
    void desc(Database& db, size_t id);
    void redesc(Database& db, size_t id, const std::string& d);

    void deanon(Database& db, size_t anon, size_t id);

    void meets(Database& db, size_t id);
    void commons(Database& db, size_t a, size_t b);

    void less(Database& db, size_t t, size_t id);
    void greater(Database& db, size_t t, size_t id);

    void outPersons(Database& db, const std::string& file);

}

#endif