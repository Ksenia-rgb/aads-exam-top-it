#include "functions.hpp"
namespace lachugin
{
  void pushBack(Person*& persons, size_t& size, size_t& capacity, const Person& person)
  {
    if (size == capacity)
    {
      size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
      Person* newPersons = new Person[newCapacity];
      for (size_t i = 0; i < size; i++)
      {
        newPersons[i] = persons[i];
      }
      delete[] persons;
      persons = newPersons;
      capacity = newCapacity;
    }
    persons[size] = person;
    size++;
  }

  bool containsId(const Person *persons, size_t size, size_t id)
  {
    for (size_t i = 0; i < size; i++)
    {
      if (persons[i].id == id)
      {
        return true;
      }
    }
    return false;
  }

  bool parseLine(const std::string& line, Person& person)
  {
    size_t index = 0;
    while (index < line.size() && std::isdigit(line[index]))
    {
      index++;
    }

    if (index == 0)
    {
      return false;
    }
    if (index < line.size() && !std::isspace(line[index]))
    {
      return false;
    }
    person.id = std::stoull(line.substr(0, index));
    while (index < line.size() && std::isspace(line[index]))
    {
      index++;
    }
    if (index >= line.size())
    {
      return false;
    }

    person.info = line.substr(index);
    return true;
  }



}
