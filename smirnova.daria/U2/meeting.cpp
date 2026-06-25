#include "meeting.h"
#include <sstream>

namespace smirnova {

    bool parseMeeting(const std::string& line, Meeting& m) {
        std::istringstream iss(line);
        if (!(iss >> m.a >> m.b >> m.t)) return false;
        return true;
    }

}