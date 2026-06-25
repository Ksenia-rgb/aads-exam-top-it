#include "person.hpp"

size_t chernov::findById(const Vector< Person > & persons, size_t id)
{
  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].id == id) {
      return i;
    }
  }
  return persons.size;
}
