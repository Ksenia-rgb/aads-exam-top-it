#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <dynamicArray.hpp>
#include "../U1/person.hpp"
#include "meet.hpp"

namespace zhuravleva
{
  void processCommands(
      std::istream &input,
      std::ostream &output,
      DynamicArray< Person > &persons,
      DynamicArray< Meet > &meets);
}

#endif