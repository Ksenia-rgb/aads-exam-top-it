#include "storage.hpp"

namespace losev
{
  void initPersonStorage(PersonStorage& storage)
  {
    storage.head = nullptr;
    storage.tail = nullptr;
  }

  void addPerson(PersonStorage& storage, const Person& person)
  {
    PersonNode* node = new PersonNode;
    node->data = person;
    node->next = nullptr;

    if (storage.tail == nullptr)
    {
      storage.head = node;
      storage.tail = node;
    }
    else
    {
      storage.tail->next = node;
      storage.tail = node;
    }
  }

  bool findPersonId(const PersonStorage& storage, size_t id)
  {
    PersonNode* current = storage.head;
    while (current != nullptr)
    {
      if (current->data.id == id)
      {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  const Person* findPerson(const PersonStorage& storage, size_t id)
  {
    PersonNode* current = storage.head;
    while (current != nullptr)
    {
      if (current->data.id == id)
      {
        return &current->data;
      }
      current = current->next;
    }
    return nullptr;
  }

  bool existsPerson(const PersonStorage& storage, size_t id)
  {
    return findPersonId(storage, id);
  }

  void clearPersonStorage(PersonStorage& storage)
  {
    PersonNode* current = storage.head;
    while (current != nullptr)
    {
      PersonNode* next = current->next;
      delete current;
      current = next;
    }
    storage.head = nullptr;
    storage.tail = nullptr;
  }

  void initMeetingStorage(MeetingStorage& storage)
  {
    storage.head = nullptr;
    storage.tail = nullptr;
  }

  void addMeeting(MeetingStorage& storage, const Meeting& meeting)
  {
    MeetingNode* node = new MeetingNode;
    node->data = meeting;
    node->next = nullptr;

    if (storage.tail == nullptr)
    {
      storage.head = node;
      storage.tail = node;
    }
    else
    {
      storage.tail->next = node;
      storage.tail = node;
    }
  }

  void clearMeetingStorage(MeetingStorage& storage)
  {
    MeetingNode* current = storage.head;
    while (current != nullptr)
    {
      MeetingNode* next = current->next;
      delete current;
      current = next;
    }
    storage.head = nullptr;
    storage.tail = nullptr;
  }
}
