#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../U1/io.hpp"
#include "meet.hpp"

#include <iostream>

namespace ulanova
{
  void runCommands(Array< Person > & persons,
      const Array< Meet > & meets,
      std::istream & in,
      std::ostream & out);
}

#endif
