#include "io.hpp"
#include <string>
#include <iostream>
#include <cstddef>

namespace losev
{
  void readPeople(std::istream& in, PersonStorage& storage)
  {
    std::string line;
    while (std::getline(in, line))
    {

    }
  }

  void readMeetings(std::istream& in, MeetingStorage& storage)
  {
    size_t id1, id2, duration;
    while (in >> id1 >> id2 >> duration)
    {
      if (id1 == id2)
      {
        continue;
      }
      Meeting m;
      m.id1 = id1;
      m.id2 = id2;
      m.duration = duration;
      addMeeting(storage, m);
    }
  }
}
