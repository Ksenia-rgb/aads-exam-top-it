#include "commands.h"

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <string>

namespace smirnova {

    // ========== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ==========

    bool isInRange(const Database& db, const Date& date) {
        if (!db.hasRange) {
            return true;
        }
        return date >= db.rangeMin && date <= db.rangeMax;
    }

    // ========== СТАРЫЕ КОМАНДЫ ==========

    void commandAnons(const Database& db, std::ostream& out) {
        for (size_t i = 0; i < db.pCount; ++i) {
            if (!db.persons[i].hasDesc) {
                out << db.persons[i].id << '\n';
            }
        }
    }

    void commandDesc(const Database& db, size_t id, std::ostream& out) {
        const Person* p = findPerson(db, id);
        if (p == nullptr) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        if (!p->hasDesc) {
            out << "<ANON>\n";
        } else {
            out << p->desc << '\n';
        }
    }

    void commandRedesc(Database& db, size_t id, const std::string& desc, std::ostream& out) {
        Person* p = findPerson(db, id);
        if (p == nullptr) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        p->desc = desc;
        p->hasDesc = true;
    }

    void commandDeanon(Database& db, size_t anonId, size_t id, std::ostream& out) {
        Person* anon = findPerson(db, anonId);
        Person* person = findPerson(db, id);

        if (anon == nullptr || person == nullptr) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        if (anon->hasDesc || !person->hasDesc) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        anon->desc = person->desc;
        anon->hasDesc = true;
    }

    void commandMeets(const Database& db, size_t id, std::ostream& out) {
        if (findPerson(db, id) == nullptr) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        struct MeetInfo {
            size_t otherId;
            size_t duration;
        };

        MeetInfo* meets = new MeetInfo[db.mCount];
        size_t count = 0;

        for (size_t i = 0; i < db.mCount; ++i) {
            const Meeting& m = db.meetings[i];

            if (!isInRange(db, m.date)) {
                continue;
            }

            if (m.a == id) {
                meets[count].otherId = m.b;
                meets[count].duration = m.duration;
                ++count;
            } else if (m.b == id) {
                meets[count].otherId = m.a;
                meets[count].duration = m.duration;
                ++count;
            }
        }

        // Сортировка: сначала по otherId, потом по duration
        for (size_t i = 0; i < count; ++i) {
            for (size_t j = i + 1; j < count; ++j) {
                if (meets[i].otherId > meets[j].otherId ||
                    (meets[i].otherId == meets[j].otherId &&
                     meets[i].duration > meets[j].duration)) {
                    MeetInfo tmp = meets[i];
                    meets[i] = meets[j];
                    meets[j] = tmp;
                }
            }
        }

        for (size_t i = 0; i < count; ++i) {
            out << meets[i].otherId << ' ' << meets[i].duration << '\n';
        }

        delete[] meets;
    }

    void commandCommons(const Database& db, size_t id1, size_t id2, std::ostream& out) {
        if (findPerson(db, id1) == nullptr || findPerson(db, id2) == nullptr) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        std::set<size_t> commonIds;

        for (size_t i = 0; i < db.mCount; ++i) {
            const Meeting& m = db.meetings[i];

            if (!isInRange(db, m.date)) {
                continue;
            }

            size_t other1 = 0;
            bool hasId1 = false;

            if (m.a == id1) {
                other1 = m.b;
                hasId1 = true;
            } else if (m.b == id1) {
                other1 = m.a;
                hasId1 = true;
            }

            if (!hasId1) {
                continue;
            }

            for (size_t j = 0; j < db.mCount; ++j) {
                const Meeting& m2 = db.meetings[j];

                if (!isInRange(db, m2.date)) {
                    continue;
                }

                if ((m2.a == id2 && m2.b == other1) ||
                    (m2.b == id2 && m2.a == other1)) {
                    if (other1 != id1 && other1 != id2) {
                        commonIds.insert(other1);
                    }
                    break;
                }
            }
        }

        for (size_t id : commonIds) {
            out << id << '\n';
        }
    }

    void commandLess(const Database& db, size_t duration, size_t id, std::ostream& out) {
        if (findPerson(db, id) == nullptr) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        struct MeetInfo {
            size_t otherId;
            size_t duration;
        };

        MeetInfo* meets = new MeetInfo[db.mCount];
        size_t count = 0;

        for (size_t i = 0; i < db.mCount; ++i) {
            const Meeting& m = db.meetings[i];

            if (!isInRange(db, m.date)) {
                continue;
            }

            if ((m.a == id || m.b == id) && m.duration < duration) {
                meets[count].otherId = (m.a == id) ? m.b : m.a;
                meets[count].duration = m.duration;
                ++count;
            }
        }

        for (size_t i = 0; i < count; ++i) {
            for (size_t j = i + 1; j < count; ++j) {
                if (meets[i].otherId > meets[j].otherId ||
                    (meets[i].otherId == meets[j].otherId &&
                     meets[i].duration > meets[j].duration)) {
                    MeetInfo tmp = meets[i];
                    meets[i] = meets[j];
                    meets[j] = tmp;
                }
            }
        }

        for (size_t i = 0; i < count; ++i) {
            out << meets[i].otherId << ' ' << meets[i].duration << '\n';
        }

        delete[] meets;
    }

    void commandGreater(const Database& db, size_t duration, size_t id, std::ostream& out) {
        if (findPerson(db, id) == nullptr) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        struct MeetInfo {
            size_t otherId;
            size_t duration;
        };

        MeetInfo* meets = new MeetInfo[db.mCount];
        size_t count = 0;

        for (size_t i = 0; i < db.mCount; ++i) {
            const Meeting& m = db.meetings[i];

            if (!isInRange(db, m.date)) {
                continue;
            }

            if ((m.a == id || m.b == id) && m.duration > duration) {
                meets[count].otherId = (m.a == id) ? m.b : m.a;
                meets[count].duration = m.duration;
                ++count;
            }
        }

        for (size_t i = 0; i < count; ++i) {
            for (size_t j = i + 1; j < count; ++j) {
                if (meets[i].otherId > meets[j].otherId ||
                    (meets[i].otherId == meets[j].otherId &&
                     meets[i].duration > meets[j].duration)) {
                    MeetInfo tmp = meets[i];
                    meets[i] = meets[j];
                    meets[j] = tmp;
                }
            }
        }

        for (size_t i = 0; i < count; ++i) {
            out << meets[i].otherId << ' ' << meets[i].duration << '\n';
        }

        delete[] meets;
    }

    void commandOutPersons(const Database& db, const std::string& filename) {
        std::ofstream out(filename.c_str());
        if (!out.is_open()) {
            return;
        }

        for (size_t i = 0; i < db.pCount; ++i) {
            if (db.persons[i].hasDesc) {
                out << db.persons[i].id << ' ' << db.persons[i].desc << '\n';
            }
        }
    }

    // ========== НОВЫЕ КОМАНДЫ ==========

    void commandRange(const Database& db, std::ostream& out) {
        if (!db.hasRange) {
            out << "<EMPTY>\n";
            return;
        }

        out << db.rangeMin.day << ' '
            << db.rangeMin.month << ' '
            << db.rangeMin.year << " : "
            << db.rangeMax.day << ' '
            << db.rangeMax.month << ' '
            << db.rangeMax.year << '\n';
    }

    void commandBefore(Database& db, size_t day, size_t month, size_t year, std::ostream& out) {
        Date date{day, month, year};

        if (!db.hasRange) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        bool hasDateBefore = false;
        for (size_t i = 0; i < db.mCount; ++i) {
            const Meeting& m = db.meetings[i];
            if (m.date < date && isInRange(db, m.date)) {
                hasDateBefore = true;
                break;
            }
        }

        if (!hasDateBefore) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        pushRange(db);
        db.rangeMax = date;

        if (db.rangeMin > db.rangeMax) {
            db.hasRange = false;
        }
    }

    void commandAfter(Database& db, size_t day, size_t month, size_t year, std::ostream& out) {
        Date date{day, month, year};

        if (!db.hasRange) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        bool hasDateAfter = false;
        for (size_t i = 0; i < db.mCount; ++i) {
            const Meeting& m = db.meetings[i];
            if (m.date > date && isInRange(db, m.date)) {
                hasDateAfter = true;
                break;
            }
        }

        if (!hasDateAfter) {
            out << "<INVALID COMMAND>\n";
            return;
        }

        pushRange(db);
        db.rangeMin = date;

        if (db.rangeMin > db.rangeMax) {
            db.hasRange = false;
        }
    }

    void commandPopRange(Database& db, std::ostream& out) {
        if (!popRange(db)) {
            out << "<INVALID COMMAND>\n";
        }
    }

}  // namespace smirnova