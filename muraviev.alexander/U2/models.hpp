#ifndef MODELS_HPP
#define MODELS_HPP

#include <cstddef>
#include <string>

namespace muraviev
{
  struct Person
  {
    size_t id;
    std::string info;
    bool hasInfo;
  };

  struct PersonNode
  {
    Person person;
    PersonNode* next;
  };

  struct PersonList
  {
    PersonNode* head;
    PersonNode* tail;
  };

  struct Meeting
  {
    size_t first;
    size_t second;
    size_t time;
  };

  struct MeetingNode
  {
    Meeting meeting;
    MeetingNode* next;
  };

  struct MeetingList
  {
    MeetingNode* head;
    MeetingNode* tail;
  };

  struct ProgramOptions
  {
    bool hasPersonsFile;
    bool hasDataFile;
    std::string personsFile;
    std::string dataFile;
  };
}

#endif
