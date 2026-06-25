#include "structures.hpp"

namespace karpenkov {
HashTable *createHashTable(size_t initCapacity) {
  HashTable *table = new HashTable;
  table->size = 0;
  table->capacity = initCapacity;
  return table;
}
void hashTableDestroy(HashTable *tableL) {
  if (!tableL)
    return;
  delete[] tableL->table;
  delete tableL;
}

} // namespace karpenkov
