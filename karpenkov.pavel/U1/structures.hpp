#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include <iostream>

namespace karpenkov {
struct Person {
  size_t id;
  std::string info;
};
struct HashPerson {
  Person unit;
  bool occupied;
};
struct HashTable {
  HashPerson *table;
  size_t size;
  size_t capacity;
};
HashTable *createHashTable(size_t initCapacity);
void hashTableDestroy();
} // namespace karpenkov
#endif
