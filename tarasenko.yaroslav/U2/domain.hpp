#ifndef TARASENKO_YAROSLAV_U2_DOMAIN_HPP
#define TARASENKO_YAROSLAV_U2_DOMAIN_HPP

#include <cstddef>
#include <memory>
#include <string>

namespace tarasenko
{
  struct PersonRecord
  {
    std::size_t id;
    std::string info;
    bool hasInfo;
  };

  struct Meeting
  {
    std::size_t first;
    std::size_t second;
    std::size_t time;
  };

  struct Database
  {
    std::unique_ptr< PersonRecord[] > persons;
    std::size_t personCount;
    std::size_t personCapacity;
    std::unique_ptr< Meeting[] > meetings;
    std::size_t meetingCount;
    std::size_t meetingCapacity;
  };

  Database makeDatabase();
  int findPersonIndex(const Database& database, std::size_t id);
  bool hasPerson(const Database& database, std::size_t id);
  void ensurePerson(Database& database, std::size_t id);
  void setPersonInfo(Database& database, std::size_t id, const std::string& info);
  void appendMeeting(Database& database, const Meeting& meeting);
}

#endif
