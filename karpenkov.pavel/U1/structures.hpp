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
struct Args {
  std::string inputFile;
  std::string outputFile;
  bool valid;
};
HashTable *createHashTable(size_t initCapacity);
void hashTableDestroy(HashTable *tableL);
void hashTableInsert(HashTable *table, const Person &person);
Person *hashTableGet(const HashTable *table, size_t id);
OrderArray *createOrderArray(size_t initCapacity);
void destroyOrderArray(OrderArray *arr);
void orderArrayPush(OrderArray *arr, size_t id);
size_t orderArrayGet(const OrderArray *arr, size_t index);
size_t orderArraySize(const OrderArray *arr);
bool processLine(const std::string &line, HashTable *table, OrderArray *order);
void goodStringsCount(std::istream &in, HashTable *table, OrderArray *order,
                      size_t &successCount, size_t &ignoredCount);
void writeData(std::ostream &out, const HashTable *table,
               const OrderArray *order);
Args processArgs(int argc, char *argv[]);
} // namespace karpenkov
#endif
