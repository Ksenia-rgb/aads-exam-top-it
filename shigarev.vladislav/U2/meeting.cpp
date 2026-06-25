#include "meeting.hpp"

#include <iostream>
#include <limits>

namespace {
  bool readNumber(std::istream& in, size_t& value)
  {
    in >> value;
    if (in.fail()) {
      return false;
    }
    return true;
  }
}

bool shigarev::readMeetings(std::istream& in,
    DynArray< Meeting >& meetings)
{
  meetings = createDynArray< Meeting >(16);
  size_t id1, id2, duration;
  while (in >> id1 >> id2 >> duration) {
    if (id1 == id2) {
      continue;
    }
    Meeting m = {id1, id2, duration};
    pushBack(meetings, m);
  }
  if (in.eof()) {
    return true;
  }
  return false;
}
