#ifndef PERSON_H_
#define PERSON_H_

#include <cstddef>
#include <ostream>
#include <string>

namespace smirnova
{
    struct Person
    {
        size_t id;
        std::string info;
    };

    bool parsePerson(const std::string &line, Person &person);
    bool isDuplicate(const Person *persons, size_t count, const Person &person);
    void printPerson(const Person &person, std::ostream &out);
}

#endif
