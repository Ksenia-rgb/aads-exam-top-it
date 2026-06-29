#ifndef LOSEV_STORAGE_HPP
#define LOSEV_STORAGE_HPP

#include "../common/person.hpp"
#include "meeting.hpp"

namespace losev
{
  struct PersonNode
  {
    Person data;
    PersonNode* next;
  };

  struct MeetingNode
  {
    Meeting data;
    MeetingNode* next;
  };

  struct PersonStorage
  {
    PersonNode* head;
    PersonNode* tail;
  };

  struct MeetingStorage
  {
    MeetingNode* head;
    MeetingNode* tail;
  };

  void initPersonStorage(PersonStorage& storage);
  void addPerson(PersonStorage& storage, const Person& person);
  bool findPersonId(const PersonStorage& storage, size_t id);
  const Person* findPerson(const PersonStorage& storage, size_t id);
  bool existsPerson(const PersonStorage& storage, size_t id);
  void clearPersonStorage(PersonStorage& storage);

  void initMeetingStorage(MeetingStorage& storage);
  void addMeeting(MeetingStorage& storage, const Meeting& meeting);
  void clearMeetingStorage(MeetingStorage& storage);
}

#endif
