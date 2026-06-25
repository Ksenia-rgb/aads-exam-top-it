#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>

namespace afanasev
{
  struct Person;
  struct Meeting;

  void processCommand(const std::string & cmdLine,
    Person *& persons, size_t & count, size_t & capacity, Meeting *& meetings, size_t & mCount);
}

#endif
