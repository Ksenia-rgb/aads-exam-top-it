#include <iostream>

namespace karpenkov {
struct Person {
  size_t id;
  std::string info;
};
struct HashPerson {
private:
  Person unit;
  bool occupied;
};
struct HashTable {
private:
  HashPerson *table_;
  size_t size_;
  size_t capacity_;
};
} // namespace karpenkov
