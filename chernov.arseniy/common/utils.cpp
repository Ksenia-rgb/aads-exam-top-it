#include "utils.hpp"

void chernov::addUniqueId(Vector< size_t > & allIds, size_t id)
{
  for (size_t i = 0; i < allIds.size; ++i) {
    if (allIds.data[i] == id) {
      return;
    }
  }
  pushBack(allIds, id);
}

bool chernov::hasId(const Vector< size_t > & allIds, size_t id)
{
  for (size_t i = 0; i < allIds.size; ++i) {
    if (allIds.data[i] == id) {
      return true;
    }
  }
  return false;
}
