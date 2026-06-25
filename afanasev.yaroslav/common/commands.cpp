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
}
