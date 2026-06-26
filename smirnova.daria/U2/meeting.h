#ifndef MEETING_H_
#define MEETING_H_

#include <cstddef>
#include <string>

namespace smirnova {

    struct Meeting {
        size_t a{};
        size_t b{};
        size_t t{};
    };

    bool parseMeeting(const std::string& line, Meeting& m);

}

#endif