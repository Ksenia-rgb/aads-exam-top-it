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
struct OrderArray {
  size_t *data;
  size_t size;
  size_t capacity;
};
HashTable *createHashTable(size_t initCapacity);
void hashTableDestroy();
void hashTableInsert(HashTable *table, const Person &person);
Person *hashTableGet(const HashTable *table, size_t id);
OrderArray *createOrderArray(size_t initCapacity);
void destroyOrderArray(OrderArray *arr);
void orderArrayPush(OrderArray *arr, size_t id);
} // namespace karpenkov
#endif
