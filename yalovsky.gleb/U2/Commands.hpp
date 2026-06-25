#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <cstddef>
#include <string>
#include <iosfwd>
#include "Database.hpp"

namespace yalovsky
{
  void cmdAnons(std::ostream& out, const Database& db);
  bool cmdDesc(std::ostream& out, const Database& db, size_t id);
  bool cmdRedesc(Database& db, size_t id, const std::string& info);
  bool cmdMeets(std::ostream& out, const Database& db, size_t id);
  bool cmdCommons(std::ostream& out, const Database& db, size_t first, size_t second);
  bool cmdBounded(std::ostream& out, const Database& db, size_t id, size_t time, bool greater);
  bool cmdOutPersons(const Database& db, const std::string& filename);
}

#endif
