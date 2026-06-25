#include "meeting.hpp"
#include <sstream>

namespace afanasev
{
  bool parseMeeting(const std::string & line, Meeting & meeting)
  {
    std::istringstream iss(line);
    if (!(iss >> meeting.id1))
    {
      return false;
    }
    if (!(iss >> meeting.id2))
    {
      return false;
    }
    if (!(iss >> meeting.duration))
    {
      return false;
    }
    return true;
  }

  void addMeeting(Meeting *& meetings, size_t & count, size_t & capacity, const Meeting & meeting)
  {
    if (count == capacity)
    {
      size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
      Meeting* newMeetings = new Meeting[newCapacity];
      for (size_t i = 0; i < count; ++i)
      {
        newMeetings[i] = meetings[i];
      }
      delete[] meetings;
      meetings = newMeetings;
      capacity = newCapacity;
    }
    meetings[count++] = meeting;
  }

  void replacePersonInMeetings(Meeting * meetings, size_t count, size_t oldId, size_t newId)
  {
    for (size_t i = 0; i < count; ++i)
    {
      if (meetings[i].id1 == oldId)
      {
        meetings[i].id1 = newId;
      }
      if (meetings[i].id2 == oldId)
      {
        meetings[i].id2 = newId;
      }
    }
  }

  void removeSelfMeetings(Meeting *& meetings, size_t & count)
  {
    size_t write = 0;
    for (size_t i = 0; i < count; ++i)
    {
      if (meetings[i].id1 != meetings[i].id2)
      {
        meetings[write++] = meetings[i];
      }
    }
    count = write;
  }
}
