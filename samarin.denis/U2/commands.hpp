#ifndef SAMARIN_U2_COMMANDS_HPP
#define SAMARIN_U2_COMMANDS_HPP

#include <iosfwd>

#include "model.hpp"

namespace samarin {
  void runCommands(std::istream & input, std::ostream & output, Dataset & data);
}

#endif
