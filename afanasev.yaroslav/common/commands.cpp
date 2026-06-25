#include "commands.hpp"
#include "person.hpp"
#include "meeting.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace afanasev
{
  bool isValidId(const Person* persons, size_t count, size_t id)
  {
    return findPersonIndex(persons, count, id) != -1;
  }

  bool isAnon(const Person* persons, size_t count, size_t id)
  {
    int idx = findPersonIndex(persons, count, id);
    if (idx == -1)
    {
      return true;
    }
    return persons[idx].info.empty();
  }


  void cmdAnons(std::istringstream &, Person *& persons, size_t & count, size_t &,
    Meeting *&, size_t &)
  {
    size_t * anonIds = new size_t[count];
    size_t anonCount = 0;
    for (size_t i = 0; i < count; ++i)
    {
      if (persons[i].info.empty())
      {
        anonIds[anonCount++] = persons[i].id;
      }
    }
    std::sort(anonIds, anonIds + anonCount);
    for (size_t i = 0; i < anonCount; ++i)
    {
      std::cout << anonIds[i] << '\n';
    }
    delete[] anonIds;
  }

  struct Command
  {
    const char * name;
    void (*handler)(std::istringstream &,
      Person *&, size_t &, size_t &, Meeting *&, size_t &);
  };

  void cmdDeanonymize(std::istringstream & iss, Person *& persons, size_t & count,
    size_t & capacity,Meeting *& meetings, size_t & mCount)
  {
    size_t anonId, id;
    if (!(iss >> anonId >> id))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (!isValidId(persons, count, anonId) || !isValidId(persons, count, id) ||
      !isAnon(persons, count, anonId) || isAnon(persons, count, id))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    replacePersonInMeetings(meetings, mCount, anonId, id);
    removeSelfMeetings(meetings, mCount);
    removePersonById(persons, count, anonId);
  }

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
