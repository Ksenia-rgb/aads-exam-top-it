#include "meeting.hpp"
#include <istream>
#include <stdexcept>

borisov::MeetingNode *borisov::readMeetings(std::istream &in)
{
  borisov::MeetingNode *head = nullptr;
  borisov::MeetingNode *tail = nullptr;
  try
  {
    size_t day = 0;
    while (in >> day)
    {
      size_t month = 0;
      size_t year = 0;
      size_t id1 = 0;
      size_t id2 = 0;
      size_t duration = 0;
      if (!(in >> month >> year >> id1 >> id2 >> duration))
      {
        throw std::runtime_error("invalid meeting data");
      }
      if (id1 == id2)
      {
        continue;
      }
      const borisov::Date date{day, month, year};
      borisov::MeetingNode * const node = new borisov::MeetingNode{
          borisov::Meeting{date, id1, id2, duration}, nullptr};
      if (tail == nullptr)
      {
        head = node;
        tail = node;
      }
      else
      {
        tail->next_ = node;
        tail = node;
      }
    }
    if (!in.eof())
    {
      throw std::runtime_error("invalid meeting data");
    }
  }
  catch (...)
  {
    borisov::freeMeetings(head);
    throw;
  }
  return head;
}

void borisov::freeMeetings(borisov::MeetingNode * const head)
{
  borisov::MeetingNode *cur = head;
  while (cur != nullptr)
  {
    borisov::MeetingNode * const next = cur->next_;
    delete cur;
    cur = next;
  }
}
