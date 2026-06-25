#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include <ostream>
#include <array.hpp>
#include <person.hpp>

namespace zharov
{
  struct Context
  {
    Array< Person >* persons;
    Array< Meet >* meets;
  };

  using Cmd = void (*)(std::ostream&, std::istream&, Context&);
  using ConstCmd = void (*)(std::ostream&, std::istream&, const Context&);

  void runAnons(std::ostream&, std::istream&, const Context&);
  void runDesc(std::ostream&, std::istream&, const Context&);
  void runMeets(std::ostream&, std::istream&, const Context&);
  void runCommons(std::ostream&, std::istream&, const Context&);
  void runLess(std::ostream&, std::istream&, const Context&);
  void runGreater(std::ostream&, std::istream&, const Context&);
  void runOutPersons(std::ostream&, std::istream&, const Context&);

  void runDeanon(std::ostream&, std::istream&, Context&);
  void runRedesc(std::ostream&, std::istream&, Context&);
}

#endif
