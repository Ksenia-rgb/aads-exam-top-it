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
}
