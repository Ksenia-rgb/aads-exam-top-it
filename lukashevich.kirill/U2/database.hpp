#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cstddef>
#include <string>

#include "array.hpp"
#include "persons.hpp"

namespace lukashevich
{
  struct Meeting
  {
    size_t first;
    size_t second;
    size_t time;
  };

  struct MeetingView
  {
    size_t id;
    size_t time;
  };

  struct Database
  {
    Array< Person > persons;
    Array< Meeting > meetings;
  };

  void initDatabase(Database& database) noexcept;
  void destroyDatabase(Database& database) noexcept;

  void addAnonPerson(Database& database, size_t id);
  bool addDescribedPerson(Database& database, size_t id, const std::string& info);
  void addMeeting(Database& database, size_t first, size_t second, size_t time);

  bool hasMeetingWith(const Database& database, size_t id, size_t other);
  bool pushUniqueId(Array< size_t >& ids, size_t id);

  void sortIds(Array< size_t >& ids);
  void sortMeetingViews(Array< MeetingView >& views);
}

#endif
