#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <string>

namespace donkeev
{
struct Person
  {
      size_t id;
      std::string info;
  };

  struct PersonNode
  {
    Person* data;
    PersonNode* next_;
    PersonNode* prev_;
  };

  struct PersonList
  {
    PersonNode* head_;
    PersonNode* tail_;
    size_t size_;
  };

  struct MeetingNode
  {
    std::pair<size_t, size_t> ids;
    size_t duration;
    MeetingNode* next_;
    MeetingNode* prev_;
  };

  struct MeetingList
  {
    MeetingNode* head_;
    MeetingNode* tail_;
    size_t size_;
  };

  struct CommandNode
  {
    std::string name;
    void(*cmd)(MeetingList&, PersonList&, std::ostream&);
    CommandNode* next_;
    CommandNode* prev_;
  };

  struct CommandList
  {
    CommandNode* head_;
    CommandNode* tail_;
    size_t size;
  };

}

#endif
