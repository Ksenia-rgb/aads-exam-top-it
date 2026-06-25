#ifndef MEETING_HPP
#define MEETING_HPP
#include <cstddef>
namespace lachugin
{
  struct Meeting
  {
    size_t firstId;
    size_t secondId;
    size_t time;
  };

  struct MeetInfo
  {
    size_t id;
    size_t time;
  };

}

#endif
