#ifndef LOSEV_COMMANDS_HPP
#define LOSEV_COMMANDS_HPP

#include <string>
#include "storage.hpp"

namespace losev
{
  void processCommand(const std::string& line, PersonStorage& people, MeetingStorage& meetings);
}

#endif
