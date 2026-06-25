#ifndef BORISOV_U3_MEETING_HPP
#define BORISOV_U3_MEETING_HPP
#include <cstddef>
#include <iosfwd>
#include "date.hpp"

namespace borisov
{
  struct Meeting
  {
    Date date_;
    size_t id1_;
    size_t id2_;
    size_t duration_;
  };

  struct MeetingNode
  {
    Meeting data_;
    MeetingNode *next_;
  };

  MeetingNode *readMeetings(std::istream &in);
  void freeMeetings(MeetingNode *head);
}

#endif
