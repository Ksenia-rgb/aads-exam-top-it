#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>

class DB;
namespace levkin {
  void anons(DB db, std::istream& is, std::ostream& os);
  void deanon(DB db, std::istream& is, std::ostream& os);
  void redesc(DB db, std::istream& is, std::ostream& os);
  void desc(DB db, std::istream& is, std::ostream& os);
  void meets(DB db, std::istream& is, std::ostream& os);
  void commons(DB db, std::istream& is, std::ostream& os);
  void less(DB db, std::istream& is, std::ostream& os);
  void greater(DB db, std::istream& is, std::ostream& os);
  void outPersons(DB db, std::istream& is, std::ostream& os);
}
#endif
