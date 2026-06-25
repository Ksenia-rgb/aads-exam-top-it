#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

#include "database.hpp"

namespace lukashevich
{
  void commandAnons(const std::string& line, Database& database, std::ostream& out);

  void commandDeanon(const std::string& line, Database& database, std::ostream& out);

  void commandRedesc(const std::string& line, Database& database, std::ostream& out);

  void commandDesc(const std::string& line, Database& database, std::ostream& out);

  void commandMeets(const std::string& line, Database& database, std::ostream& out);

  void commandCommons(const std::string& line, Database& database, std::ostream& out);

  void commandLess(const std::string& line, Database& database, std::ostream& out);

  void commandGreater(const std::string& line, Database& database, std::ostream& out);

  void commandOutPersons(const std::string& line, Database& database, std::ostream& out);
}

#endif
