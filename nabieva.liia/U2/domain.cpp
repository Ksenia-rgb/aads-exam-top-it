#include "domain.hpp"

namespace kirilich
{
  void init(Database& database)
  {
    init(database.persons);
    init(database.meetings);
  }

  void clear(Database& database)
  {
    clear(database.meetings);
    clear(database.persons);
  }
}