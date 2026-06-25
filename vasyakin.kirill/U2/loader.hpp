#ifndef LOADER_HPP
#define LOADER_HPP

#include <iosfwd>
#include "model.hpp"

namespace vasyakin
{
  void loadPersons(std::istream& in, Graph*& root);
  bool loadMeetings(std::istream& in, Graph*& root);
}

#endif
