#ifndef LOADER_HPP
#define LOADER_HPP

#include <iosfwd>

#include "model.hpp"

namespace burukov
{

  void loadPersons(std::istream& in, Graph& graph);
  bool loadMeetings(std::istream& in, Graph& graph);

}

#endif
