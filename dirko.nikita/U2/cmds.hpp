#ifndef CMDS_HPP
#define CMDS_HPP

#include <iosfwd>
#include <string>
#include "meet.hpp"

namespace dirko
{
  void processCommand(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &meets,
                      const std::string &command);
}

#endif
