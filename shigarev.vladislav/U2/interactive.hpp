#ifndef INTERACTIVE_HPP
#define INTERACTIVE_HPP

#include "dynarray.hpp"
#include "person.hpp"
#include "meeting.hpp"

namespace shigarev {
  void runInteractive(DynArray< Person >& persons,
      DynArray< Meeting >& meetings);

  void ensurePersonExists(DynArray< Person >& persons,
      size_t id);
}

#endif
