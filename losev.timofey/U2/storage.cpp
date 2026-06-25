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

  void getMeetingsById(const MeetingStorage& storage, size_t id, MeetingNode*& resultHead, MeetingNode*& resultTail)
  {
    resultHead = nullptr;
    resultTail = nullptr;

    MeetingNode* current = storage.head;
    while (current != nullptr)
    {
      if (current->data.id1 == id || current->data.id2 == id)
      {
        MeetingNode* node = new MeetingNode;
        node->data = current->data;
        node->next = nullptr;

        if (resultTail == nullptr)
        {
          resultHead = node;
          resultTail = node;
        }
        else
        {
          resultTail->next = node;
          resultTail = node;
        }
      }
      current = current->next;
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
