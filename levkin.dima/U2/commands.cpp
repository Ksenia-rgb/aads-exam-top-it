#include "commands.hpp"
#include "utils.hpp"

namespace levkin {
  void anons(const DB& db, std::ostream& os)
  {
    Vec< size_t > anon_ids;
    for (size_t i = 0; i < db.persons.size; ++i) {
      if (db.persons.data[i].second.empty()) {
        pushBack(anon_ids, db.persons.data[i].first);
      }
    }

    selectionSort(anon_ids);

    for (size_t i = 0; i < anon_ids.size; ++i) {
      os << anon_ids.data[i] << "\n";
    }
    freeVec(anon_ids);
  }
}
