#ifndef DB_HPP
#define DB_HPP
#include <cstddef>
#include "utils.hpp"

namespace levkin {
  struct Meeting
  {
    size_t id1;
    size_t id2;
    size_t duration;
  };
  struct DB
  {
    Vec< levkin::Pair > persons;
    Vec< Meeting > meetings;
  };
}
#endif
