#include "person.hpp"

void alekseev::initPersonArray(PersonArray& persons)
{
  persons.data = nullptr;
  persons.size = 0;
  persons.capacity = 0;
}

void alekseev::destroyPersonArray(PersonArray& persons)
{
  delete[] persons.data;
  persons.data = nullptr;
  persons.size = 0;
  persons.capacity = 0;
}
