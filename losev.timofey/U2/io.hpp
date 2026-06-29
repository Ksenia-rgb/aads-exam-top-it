#ifndef LOSEV_IO_HPP
#define LOSEV_IO_HPP

#include <iosfwd>
#include "storage.hpp"

namespace losev
{
  void readPeople(std::istream& in, PersonStorage& storage);
  void readMeetings(std::istream& in, MeetingStorage& storage);
}

#endif
