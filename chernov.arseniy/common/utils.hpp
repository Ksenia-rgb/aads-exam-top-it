#ifndef UTILS_HPP
#define UTILS_HPP

#include "meeting.hpp"
#include "person.hpp"
#include "vector.hpp"

namespace chernov {

  void addUniqueId(Vector< size_t > & allIds, size_t id);
  bool hasId(const Vector< size_t > & allIds, size_t id);
  void rebuildAllIds(Vector< size_t > & allIds, const Vector< Person > & persons, const Vector< Meeting > & meetings);

}

#endif
