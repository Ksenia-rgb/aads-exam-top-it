#include "commands.h"
#include <iostream>
#include <fstream>
#include <set>

namespace smirnova {

    void anons(Database& db) {
        for (size_t i = 0; i < db.pCount; ++i)
            if (!db.persons[i].hasDesc)
                std::cout << db.persons[i].id << "\n";
    }

    void desc(Database& db, size_t id) {
        auto p = findPerson(db, id);
        if (!p) return;

        if (!p->hasDesc) std::cout << "<ANON>\n";
        else std::cout << p->desc << "\n";
    }

    void redesc(Database& db, size_t id, const std::string& d) {
        auto p = findPerson(db, id);
        if (!p) return;

        p->desc = d;
        p->hasDesc = true;
    }

    void deanon(Database& db, size_t anon, size_t id) {
        auto a = findPerson(db, anon);
        auto b = findPerson(db, id);

        if (!a || !b || a->hasDesc || !b->hasDesc) {
            std::cerr << "<INVALID COMMAND>\n";
            return;
        }

        a->desc = b->desc;
        a->hasDesc = true;
    }

    void meets(Database& db, size_t id) {
        for (size_t i = 0; i < db.mCount; ++i) {
            auto& m = db.meetings[i];

            if (m.a == id)
                std::cout << m.b << " " << m.t << "\n";
            else if (m.b == id)
                std::cout << m.a << " " << m.t << "\n";
        }
    }

    void commons(Database& db, size_t a, size_t b) {
        std::set<size_t> res;

        for (size_t i = 0; i < db.mCount; ++i) {
            auto& m = db.meetings[i];
            if ((m.a == a && m.b == b) || (m.a == b && m.b == a))
                res.insert(m.a == a ? m.b : m.a);
        }

        for (auto x : res)
            std::cout << x << "\n";
    }

    void less(Database& db, size_t t, size_t id) {
        for (size_t i = 0; i < db.mCount; ++i) {
            auto& m = db.meetings[i];
            if ((m.a == id || m.b == id) && m.t < t)
                std::cout << m.a << " " << m.b << " " << m.t << "\n";
        }
    }

    void greater(Database& db, size_t t, size_t id) {
        for (size_t i = 0; i < db.mCount; ++i) {
            auto& m = db.meetings[i];
            if ((m.a == id || m.b == id) && m.t > t)
                std::cout << m.a << " " << m.b << " " << m.t << "\n";
        }
    }

    void outPersons(Database& db, const std::string& file) {
        std::ofstream out(file);

        for (size_t i = 0; i < db.pCount; ++i)
            if (db.persons[i].hasDesc)
                out << db.persons[i].id << " " << db.persons[i].desc << "\n";
    }

}