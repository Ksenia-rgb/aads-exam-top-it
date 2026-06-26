#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <cstddef>

namespace smirnova {

    struct Person {
        size_t id{};
        std::string desc;
        bool hasDesc{false};
    };

    bool parsePerson(const std::string& line, Person& p);

}

#endif