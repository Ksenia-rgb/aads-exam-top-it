#include "structures.hpp"
#include <stdexcept>

namespace karpenkov {
size_t HashFunction(size_t id, size_t capacity) { return id % capacity; }
HashTable *createHashTable(size_t initCapacity) {
  HashTable *table = new HashTable;
  table->size = 0;
  table->capacity = initCapacity;
  return table;
}
void hashTableDestroy(HashTable *tableL) {
  if (!tableL)
    throw std::runtime_error("hashTable is already empty");
  delete[] tableL->table;
  delete tableL;
}
void hashTableInsert(HashTable *tableL, const Person &person) {
  if (tableL->capacity == 0) {
    tableL = createHashTable(16);
  }
  size_t index = HashFunction(person.id, tableL->capacity);
  while (tableL->table[index].occupied) {
    index = (index + 1) % tableL->capacity;
  }
  tableL->table[index].unit.id = person.id;
  tableL->table[index].unit.info = person.info;
  tableL->table[index].occupied = true;
  tableL->size++;
}
Person *hashTableGet(const HashTable *table, size_t id) {
  if (table->capacity == 0)
    throw std::runtime_error("Hashtable is empty");
  size_t index = HashFunction(id, table->capacity);
  size_t start = index;
  while (table->table[index].occupied) {
    if (table->table[index].unit.id == id) {
      return &table->table[index].unit;
    }
    index = (index + 1) % table->capacity;
    if (index == start) {
      return nullptr;
    }
  }

  return nullptr;
}

} // namespace karpenkov
