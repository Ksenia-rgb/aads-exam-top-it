#ifndef MEETING_HPP
#define MEETING_HPP

#include <string>

namespace afanasev
{
  struct Meeting
  {
    size_t id1;
    size_t id2;
    int duration;
  };

  bool parseMeeting(const std::string & line, Meeting & meeting);
  void addMeeting(Meeting *& meetings, size_t & count, size_t & capacity, const Meeting & meeting);
  void replacePersonInMeetings(Meeting * meetings, size_t count, size_t oldId, size_t newId);
  void removeSelfMeetings(Meeting *& meetings, size_t & count);
}

#endif
