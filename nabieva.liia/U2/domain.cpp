#include "domain.hpp"

namespace nabieva
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