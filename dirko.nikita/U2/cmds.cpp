#include "cmds.hpp"
#include <iostream>
#include <string>

namespace
{
  struct Command
  {
    const char *name;
    void (*handler)(std::istream &input, std::ostream &output, dirko::Vector< dirko::Person > &persons,
                    dirko::Vector< dirko::Meet > &meets);
  };

  const Command COMMANDS[] = {{"anons", dirko::cmdAnons},     {"deanon", dirko::cmdDeanon},
                              {"redesc", dirko::cmdRedesc},   {"desc", dirko::cmdDesc},
                              {"meet", dirko::cmdMeets},      {"meets", dirko::cmdMeets},
                              {"commons", dirko::cmdCommons}, {"less", dirko::cmdLess},
                              {"greater", dirko::cmdGreater}, {"out-persons", dirko::cmdOutPersons}};

  const size_t COMMANDS_COUNT = 10;
}

void dirko::processCommand(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &meets,
                           const std::string &command)
{
  for (size_t i = 0; i < COMMANDS_COUNT; ++i) {
    if (command == COMMANDS[i].name) {
      COMMANDS[i].handler(input, output, persons, meets);
      return;
    }
  }
  output << "<INVALID COMMAND>\n";
  while (input.get() != '\n') {
    if (!input) {
      break;
    }
  }
}
