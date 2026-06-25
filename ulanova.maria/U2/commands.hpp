#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../common/io.hpp"
#include "meet.hpp"

#include <iostream>

namespace ulanova
{
  void runCommands(Array< Person > & persons,
      Array< Meet > & meets,
      std::istream & in,
      std::ostream & out);
}

#endif
