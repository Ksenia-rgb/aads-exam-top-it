#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>

#include "model.hpp"

namespace burukov
{

  void runCommands(std::istream& in, std::ostream& out, Graph& graph);

}

#endif
