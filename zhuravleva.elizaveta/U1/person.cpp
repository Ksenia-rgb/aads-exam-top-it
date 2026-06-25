#include "person.hpp"

namespace
{
  const size_t defaultCapacity = 8;
}

void zhuravleva::init(PersonArray &persons)
{
  persons.data = nullptr;
  persons.size = 0;
  persons.capacity = 0;
}

void zhuravleva::destroy(PersonArray &persons)
{
  delete[] persons.data;
  persons.data = nullptr;
  persons.size = 0;
  persons.capacity = 0;
}

void zhuravleva::reserve(PersonArray &persons, size_t capacity)
{
  if (capacity <= persons.capacity)
  {
    return;
  }
  Person *newData = new Person[capacity];
  try
  {
    for (size_t i = 0; i < persons.size; ++i)
    {
      newData[i] = persons.data[i];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }
  delete[] persons.data;
  persons.data = newData;
  persons.capacity = capacity;
}

void zhuravleva::pushBack(PersonArray &persons, const Person &person)
{
  if (persons.size == persons.capacity)
  {
    const size_t newCapacity = (persons.capacity == 0) ? defaultCapacity : persons.capacity * 2;
    reserve(persons, newCapacity);
  }
  persons.data[persons.size] = person;
  ++persons.size;
}

bool zhuravleva::contains(const PersonArray &persons, size_t id)
{
  for (size_t i = 0; i < persons.size; ++i)
  {
    if (persons.data[i].id == id)
    {
      return true;
    }
  }
  return false;
}
