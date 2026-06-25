#include "person.h"

#include <cctype>
#include <cstdlib>

namespace smirnova
{
    bool parsePerson(const std::string &line, Person &person)
    {
        if (line.empty())
        {
            return false;
        }

        size_t pos = 0;

        while (
                pos < line.size()
                && std::isspace(static_cast< unsigned char >(line[pos]))
                )
        {
            ++pos;
        }

        if (pos >= line.size())
        {
            return false;
        }

        std::string idStr;

        while (
                pos < line.size()
                && !std::isspace(static_cast< unsigned char >(line[pos]))
                )
        {
            idStr.push_back(line[pos]);
            ++pos;
        }

        char *endPtr = nullptr;

        const unsigned long value =
                std::strtoul(idStr.c_str(), &endPtr, 10);

        if (*endPtr != '\0')
        {
            return false;
        }

        person.id = static_cast< size_t >(value);

        while (
                pos < line.size()
                && std::isspace(static_cast< unsigned char >(line[pos]))
                )
        {
            ++pos;
        }

        if (pos >= line.size())
        {
            return false;
        }

        person.info = line.substr(pos);

        while (
                !person.info.empty()
                && std::isspace(
                        static_cast< unsigned char >(person.info.back())
                )
                )
        {
            person.info.pop_back();
        }

        return !person.info.empty();
    }

    bool isDuplicate(
            const Person *persons,
            size_t count,
            const Person &person
    )
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (persons[i].id == person.id)
            {
                return true;
            }
        }

        return false;
    }

    void printPerson(
            const Person &person,
            std::ostream &out
    )
    {
        out << person.id << ' ' << person.info << '\n';
    }
}