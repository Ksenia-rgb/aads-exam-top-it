#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include "model.hpp"

namespace sedov
{
  void runCommands(std::istream & in, std::ostream & out, Graph *& root);
}

#endif
