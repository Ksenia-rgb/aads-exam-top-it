#include "meeting.h"

#include <sstream>
#include <cctype>

namespace smirnova {

    bool operator<(const Date& a, const Date& b) {
        if (a.year != b.year) return a.year < b.year;
        if (a.month != b.month) return a.month < b.month;
        return a.day < b.day;
    }

    bool operator>(const Date& a, const Date& b) {
        return b < a;
    }

    bool operator==(const Date& a, const Date& b) {
        return a.day == b.day && a.month == b.month && a.year == b.year;
    }

    bool operator!=(const Date& a, const Date& b) {
        return !(a == b);
    }

    bool operator<=(const Date& a, const Date& b) {
        return (a < b) || (a == b);
    }

    bool operator>=(const Date& a, const Date& b) {
        return (a > b) || (a == b);
    }

    bool parseMeeting(const std::string& line, Meeting& m) {
        if (line.empty()) {
            return false;
        }

        std::istringstream iss(line);

        // Читаем: день месяц год id1 id2 длительность
        if (!(iss >> m.date.day >> m.date.month >> m.date.year >> m.a >> m.b >> m.duration)) {
            return false;
        }

        // Встречи с самим собой - НЕ ошибка, просто возвращаем false
        // Но loadDataFiles должна это обрабатывать как НЕ ошибку
        if (m.a == m.b) {
            return false;
        }

        return true;
    }

}  // namespace smirnova