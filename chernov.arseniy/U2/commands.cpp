#include "commands.hpp"
#include <sort.hpp>

void chernov::printAnons(const Vector< size_t > & allIds, const Vector< Person > & persons)
{
  Vector< size_t > idsCopy;
  init(idsCopy);

  try {
    for (size_t i = 0; i < allIds.size; ++i) {
      pushBack(idsCopy, allIds.data[i]);
    }

    bubbleSort(idsCopy);

    for (size_t i = 0; i < idsCopy.size; ++i) {
      size_t id = idsCopy.data[i];
      if (findById(persons, id) == persons.size) {
        std::cout << id << '\n';
      }
    }
  } catch (...) {
    destroy(idsCopy);
    throw;
  }

  destroy(idsCopy);
}
