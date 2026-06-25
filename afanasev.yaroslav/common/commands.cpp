#include "commands.hpp"
#include "person.hpp"
#include "meeting.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

namespace afanasev
{
  struct Command
  {
    const char * name;
    void (*handler)(std::istringstream &,
      Person *&, size_t &, size_t &, Meeting *&, size_t &);
  };

  const Command commands[] =
  {
    {"anons",        cmdAnons},
    {"deanon",       cmdDeanonymize},
    {"redesc",       cmdRedesc},
    {"desc",         cmdDesc},
    {"meets",        cmdMeets},
    {"commons",      cmdCommons},
    {"less",         cmdLess},
    {"greater",      cmdGreater},
    {"out-persons",  cmdOutPersons}
  };
  const size_t COMMANDS_COUNT = sizeof(commands) / sizeof(commands[0]);

  void processCommand(const std::string & cmdLine, Person *& persons, size_t & count,
    size_t & capacity, Meeting *& meetings, size_t & mCount)
  {
    std::istringstream iss(cmdLine);
    std::string commandName;
    iss >> commandName;
    if (commandName.empty())
    {
      return;
    }

    for (size_t i = 0; i < COMMANDS_COUNT; ++i)
    {
      if (commandName == commands[i].name)
      {
        commands[i].handler(iss, persons, count, capacity, meetings, mCount);
        return;
      }
    }
    std::cout << "<INVALID COMMAND>\n";
  }
}
