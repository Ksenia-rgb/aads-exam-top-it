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

  void destroyPersonArray(personArr* array)
  {
    if (array != nullptr)
    {
      delete[] array->data;
      delete array;
    }
  }

  void pushPerson(personArr* array, const Person& person)
  {
    if (array->size == array->capacity)
    {
      size_t newCapacity = array->capacity * CAP_FACTOR;
      Person* newData = new Person[newCapacity];
      try
      {
        for (size_t i = 0; i < array->size; ++i)
        {
          newData[i] = array->data[i];
        }
      }
      catch (...)
      {
        delete[] newData;
        throw;
      }
      delete[] array->data;
      array->data = newData;
      array->capacity = newCapacity;
    }
    array->data[array->size] = person;
    ++array->size;
  }

  bool isDuplicate(const personArr* array, size_t id)
  {
    for (size_t i = 0; i < array->size; ++i)
    {
      if (array->data[i].id == id)
      {
        return true;
      }
    }
    return false;
  }
}
