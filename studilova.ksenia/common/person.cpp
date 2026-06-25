#include "person.hpp"

namespace
{
  size_t getNextCapacity(size_t capacity)
  {
    if (capacity == 0)
    {
      return 4;
    }
    return capacity * 2;
  }

  void reservePersonArray(studilova::PersonArray &array, size_t newCapacity)
  {
    if (newCapacity <= array.capacity_)
    {
      return;
    }

    studilova::Person* newData = new studilova::Person[ newCapacity ];

    for (size_t i = 0; i < array.size_; ++i)
    {
      newData[i] = array.data_[i];
    }

    delete[] array.data_;

    array.data_ = newData;
    array.capacity_ = newCapacity;
  }
}

void studilova::initPersonArray(PersonArray &array)
{
  array.data_ = nullptr;
  array.size_ = 0;
  array.capacity_ = 0;
}

void studilova::destroyPersonArray(PersonArray &array)
{
  delete[] array.data_;
  array.data_ = nullptr;
  array.size_ = 0;
  array.capacity_ = 0;
}

void studilova::appendPerson(PersonArray &array, const Person &person)
{
  if (array.size_ == array.capacity_)
  {
    reservePersonArray(array, getNextCapacity(array.capacity_));
  }

  array.data_[array.size_] = person;
  ++array.size_;
}

bool studilova::containsPersonId(const PersonArray &array, std::size_t id)
{
  for (std::size_t i = 0; i < array.size_; ++i)
  {
    if (array.data_[i].id_ == id)
    {
      return true;
    }
  }
  return false;
}
