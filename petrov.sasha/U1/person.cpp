#include "person.hpp"

#include <new>
#include <cctype>

namespace petrov
{
  const size_t CAP_FACTOR = 2;

  personArr* createPersonArray(size_t capacity)
  {
    Person* newData = new Person[capacity];
    personArr* array = nullptr;
    try
    {
      array = new personArr;
      array->data = newData;
      array->size = 0;
      array->capacity = capacity;
    }
    catch (...)
    {
      delete[] newData;
      throw;
    }
    return array;
  }
}
