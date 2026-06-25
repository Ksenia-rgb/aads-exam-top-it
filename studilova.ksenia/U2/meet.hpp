#ifndef MEET_HPP
#define MEET_HPP

#include <cstddef>

namespace studilova
{
  struct Meet
  {
    size_t firstId_;
    size_t secondId_;
    size_t duration_;
  };

  struct MeetArray
  {
    Meet* data_;
    std::size_t size_;
    std::size_t capacity_;
  };

  void initMeetArray(MeetArray &array);
  void destroyMeetArray(MeetArray &array);
  void appendMeet(MeetArray &array, const Meet &meet);
}

#endif
