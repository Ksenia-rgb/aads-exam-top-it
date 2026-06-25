#include "storage.hpp"

namespace muraviev
{
  void initPersons(PersonList& persons)
  {
    persons.head = nullptr;
    persons.tail = nullptr;
  }

  void clearPersons(PersonList& persons)
  {
    while (persons.head != nullptr)
    {
      PersonNode* const next = persons.head->next;
      delete persons.head;
      persons.head = next;
    }
    persons.tail = nullptr;
  }

  PersonNode* findPerson(PersonList& persons, const size_t id)
  {
    PersonNode* current = persons.head;
    while (current != nullptr)
    {
      if (current->person.id == id)
      {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  const PersonNode* findPerson(const PersonList& persons, const size_t id)
  {
    const PersonNode* current = persons.head;
    while (current != nullptr)
    {
      if (current->person.id == id)
      {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  bool addPerson(PersonList& persons, const size_t id,
      const std::string& info, const bool hasInfo)
  {
    if (findPerson(persons, id) != nullptr)
    {
      return false;
    }
    PersonNode* const node = new PersonNode{{id, info, hasInfo}, nullptr};
    if (persons.tail == nullptr)
    {
      persons.head = node;
    }
    else
    {
      persons.tail->next = node;
    }
    persons.tail = node;
    return true;
  }

  bool ensurePerson(PersonList& persons, const size_t id)
  {
    if (findPerson(persons, id) != nullptr)
    {
      return true;
    }
    return addPerson(persons, id, "", false);
  }

  bool removePerson(PersonList& persons, const size_t id)
  {
    PersonNode* previous = nullptr;
    PersonNode* current = persons.head;
    while (current != nullptr && current->person.id != id)
    {
      previous = current;
      current = current->next;
    }
    if (current == nullptr)
    {
      return false;
    }
    if (previous == nullptr)
    {
      persons.head = current->next;
    }
    else
    {
      previous->next = current->next;
    }
    if (persons.tail == current)
    {
      persons.tail = previous;
    }
    delete current;
    return true;
  }

  void initMeetings(MeetingList& meetings)
  {
    meetings.head = nullptr;
    meetings.tail = nullptr;
  }

  void clearMeetings(MeetingList& meetings)
  {
    while (meetings.head != nullptr)
    {
      MeetingNode* const next = meetings.head->next;
      delete meetings.head;
      meetings.head = next;
    }
    meetings.tail = nullptr;
  }

  void addMeeting(MeetingList& meetings, const size_t first,
      const size_t second, const size_t time)
  {
    MeetingNode* const node = new MeetingNode{{first, second, time}, nullptr};
    if (meetings.tail == nullptr)
    {
      meetings.head = node;
    }
    else
    {
      meetings.tail->next = node;
    }
    meetings.tail = node;
  }

  void mergePersonMeetings(MeetingList& meetings, const size_t source,
      const size_t target)
  {
    MeetingNode* previous = nullptr;
    MeetingNode* current = meetings.head;
    while (current != nullptr)
    {
      if (current->meeting.first == source)
      {
        current->meeting.first = target;
      }
      if (current->meeting.second == source)
      {
        current->meeting.second = target;
      }
      if (current->meeting.first == current->meeting.second)
      {
        MeetingNode* const removed = current;
        current = current->next;
        if (previous == nullptr)
        {
          meetings.head = current;
        }
        else
        {
          previous->next = current;
        }
        if (meetings.tail == removed)
        {
          meetings.tail = previous;
        }
        delete removed;
      }
      else
      {
        previous = current;
        current = current->next;
      }
    }
  }
}
