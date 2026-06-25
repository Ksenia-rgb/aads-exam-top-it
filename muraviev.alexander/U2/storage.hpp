#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "models.hpp"

#include <string>

namespace muraviev
{
  void initPersons(PersonList& persons);
  void clearPersons(PersonList& persons);
  PersonNode* findPerson(PersonList& persons, size_t id);
  const PersonNode* findPerson(const PersonList& persons, size_t id);
  bool addPerson(PersonList& persons, size_t id, const std::string& info,
      bool hasInfo);
  bool ensurePerson(PersonList& persons, size_t id);
  bool removePerson(PersonList& persons, size_t id);

  void initMeetings(MeetingList& meetings);
  void clearMeetings(MeetingList& meetings);
  void addMeeting(MeetingList& meetings, size_t first, size_t second,
      size_t time);
  void mergePersonMeetings(MeetingList& meetings, size_t source,
      size_t target);
}

#endif
