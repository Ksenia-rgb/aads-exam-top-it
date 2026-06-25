#include "structures.hpp"
#include <stdexcept>

namespace karpenkov {
size_t HashFunction(size_t id, size_t capacity) { return id % capacity; }
HashTable *createHashTable(size_t initCapacity) {
  HashTable *table = new HashTable;
  table->size = 0;
  table->capacity = initCapacity;
  table->table = new HashPerson[initCapacity];
  for (size_t i = 0; i < initCapacity; ++i) {
    table->table[i].occupied = false;
  }
  return table;
}
void hashTableDestroy(HashTable *tableL) {
  if (!tableL)
    return;
  delete[] tableL->table;
  delete tableL;
}
void hashTableInsert(HashTable *tableL, const Person &person) {
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
    return nullptr;
  size_t index = HashFunction(id, table->capacity);
  size_t start = index;
  while (table->table[index].occupied) {
    if (table->table[index].unit.id == id) {
      return &table->table[index].unit;
    }
    index = (index + 1) % table->capacity;
    if (index == start) {
      break;
    }
  }

  return nullptr;
}
OrderArray *createOrderArray(size_t initCapacity) {
  OrderArray *arr = new OrderArray;
  arr->data = new size_t[initCapacity];
  arr->size = 0;
  arr->capacity = initCapacity;
  return arr;
}
void destroyOrderArray(OrderArray *arr) {
  if (!arr) {
    return;
  }
  delete[] arr->data;
  delete arr;
}
void orderArrayPush(OrderArray *arr, size_t id) {
  if (arr->size >= arr->capacity) {
    size_t newCapacity = arr->capacity * 2;
    size_t *newData = new size_t[newCapacity];
    for (size_t i = 0; i < arr->size; ++i) {
      newData[i] = arr->data[i];
    }
    delete[] arr->data;
    arr->data = newData;
    arr->capacity = newCapacity;
  }
  arr->data[arr->size++] = id;
}
size_t orderArrayGet(const OrderArray *arr, size_t index) {
  return arr->data[index];
}
size_t orderArraySize(const OrderArray *arr) { return arr->size; }
bool processLine(const std::string &line, HashTable *table, OrderArray *order) {
  const char *str = line.c_str();
  while (*str && (*str == ' ' || *str == '\t')) {
    ++str;
  }
  if (!*str)
    return false;

  char *endptr;
  unsigned long long id = strtoull(str, &endptr, 10);
  if (endptr == str)
    return false;

  while (*endptr && (*endptr == ' ' || *endptr == '\t')) {
    ++endptr;
  }

  std::string info = endptr;
  if (info.empty())
    return false;

  if (hashTableGet(table, id) != nullptr)
    return false;

  Person person;
  person.id = id;
  person.info = info;
  hashTableInsert(table, person);
  orderArrayPush(order, id);

  return true;
}
void goodStringsCount(std::istream &in, HashTable *table, OrderArray *order,
                      size_t &successCount, size_t &ignoredCount) {
  std::string line;
  successCount = 0;
  ignoredCount = 0;
  while (std::getline(in, line)) {
    if (line.empty()) {
      continue;
    }
    if (processLine(line, table, order)) {
      ++successCount;
    } else {
      ++ignoredCount;
    }
  }
}
void writeData(std::ostream &out, const HashTable *table,
               const OrderArray *order) {
  for (size_t i = 0; i < orderArraySize(order); ++i) {
    size_t id = orderArrayGet(order, i);
    const Person *person = hashTableGet(table, id);
    if (person) {
      out << person->id << " " << person->info << '\n';
    }
  }
}
Args processArgs(int argc, char *argv[]) {
  Args args;
  args.inputFile = "";
  args.outputFile = "";
  args.valid = true;
  bool hasInput = false;
  bool hasOutput = false;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.rfind("in:", 0) == 0) {
      if (hasInput) {
        args.valid = false;
        return args;
      }
      args.inputFile = arg.substr(3);
      hasInput = true;
    } else if (arg.rfind("out:", 0) == 0) {
      if (hasOutput) {
        args.valid = false;
        return args;
      }
      args.outputFile = arg.substr(4);
      hasOutput = true;
    } else {
      args.valid = false;
      return args;
    }
  }
  return args;
}
} // namespace karpenkov
