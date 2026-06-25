#ifndef UTILS_HPP
#define UTILS_HPP

#include "vector.hpp"

namespace chernov {

  void addUniqueId(Vector< size_t > & allIds, size_t id);
  bool hasId(const Vector< size_t > & allIds, size_t id);

}

#endif
