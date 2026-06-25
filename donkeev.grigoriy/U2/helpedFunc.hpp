#ifndef HELPEDFUNC_HPP
#define HELPEDFUNC_HPP

#include "structs.hpp"
#include <string>
#include <iostream>

namespace donkeev
{
  void pushBack(PersonList&, Person*);
  bool isUniqueId(const PersonList&, size_t);
  bool isNumber(const std::string&);
  std::string nextWord(const std::string&, size_t&);
  void readingPersons(std::istream&, PersonList&, size_t&);

  void pushMeeting(MeetingList&, size_t, size_t, size_t);
  void clearMeetingList(MeetingList&);
  Person* findPerson(const PersonList&, size_t);
}
#endif
