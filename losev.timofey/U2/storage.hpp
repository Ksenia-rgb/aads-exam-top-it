#ifndef LOSEV_STORAGE_HPP
#define LOSEV_STORAGE_HPP

#include <vector>
#include "../common/person.hpp"
#include "meeting.hpp"

namespace losev
{
  struct PersonStorage
  {
    std::vector<Person> people;
  };

  struct MeetingStorage
  {
    std::vector<Meeting> meetings;
  };
}

#endif
