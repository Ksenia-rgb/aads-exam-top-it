#include "person.h"
#include <cctype>
#include <cstdlib>

namespace smirnova {

    bool parsePerson(const std::string& line, Person& p) {
        size_t i = 0;

        while (i < line.size() && std::isspace(line[i])) ++i;
        if (i >= line.size()) return false;

        std::string idStr;
        while (i < line.size() && !std::isspace(line[i])) {
            idStr += line[i++];
        }

        char* end = nullptr;
        unsigned long id = std::strtoul(idStr.c_str(), &end, 10);
        if (*end != '\0') return false;

        while (i < line.size() && std::isspace(line[i])) ++i;

        p.id = id;
        p.desc = line.substr(i);
        p.hasDesc = !p.desc.empty();

        return true;
    }

}