#include "db.hpp"
#include "db.hpp"

namespace levkin {
  void freeDB(DB& db)
  {
    freeVec(db.persons);
    freeVec(db.meetings);
  }

}
