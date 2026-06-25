#ifndef MEETING_H_
#define MEETING_H_

#include <cstddef>
#include <string>

namespace smirnova {

    struct Date {
        size_t day;
        size_t month;
        size_t year;
    };

    bool operator<(const Date& a, const Date& b);
    bool operator>(const Date& a, const Date& b);
    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);
    bool operator<=(const Date& a, const Date& b);
    bool operator>=(const Date& a, const Date& b);

    struct Meeting {
        size_t a{};
        size_t b{};
        size_t duration{};
        Date date{};
    };

    bool parseMeeting(const std::string& line, Meeting& m);

}

#endif  // MEETING_H_