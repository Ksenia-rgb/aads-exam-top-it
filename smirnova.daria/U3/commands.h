#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "database.h"
#include <ostream>

namespace smirnova {

    void commandAnons(const Database& db, std::ostream& out);
    void commandDesc(const Database& db, size_t id, std::ostream& out);
    void commandRedesc(Database& db, size_t id, const std::string& desc, std::ostream& out);
    void commandDeanon(Database& db, size_t anonId, size_t id, std::ostream& out);
    void commandMeets(const Database& db, size_t id, std::ostream& out);
    void commandCommons(const Database& db, size_t id1, size_t id2, std::ostream& out);
    void commandLess(const Database& db, size_t duration, size_t id, std::ostream& out);
    void commandGreater(const Database& db, size_t duration, size_t id, std::ostream& out);
    void commandOutPersons(const Database& db, const std::string& filename);

    // Новые команды для 3-го задания
    void commandRange(const Database& db, std::ostream& out);
    void commandBefore(Database& db, size_t day, size_t month, size_t year, std::ostream& out);
    void commandAfter(Database& db, size_t day, size_t month, size_t year, std::ostream& out);
    void commandPopRange(Database& db, std::ostream& out);

    bool isInRange(const Database& db, const Date& date);

}

#endif  // COMMANDS_H_