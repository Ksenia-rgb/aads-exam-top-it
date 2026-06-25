#include "person.hpp"
#include <sstream>

namespace afanasev
{
  bool parseLine(const std::string & line, Person & person)
  {
    std::istringstream iss(line);
    if (!(iss >> person.id))
    {
      return false;
    }

    iss >> std::ws;
    if (!std::getline(iss, person.info))
    {
      return false;
    }
    return !person.info.empty();
  }

  void addPerson(Person *& persons, size_t & count, size_t & capacity, const Person & person)
  {
    if (count == capacity)
    {
      size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
      Person * newPersons = new Person[newCapacity];

      for (size_t i = 0; i < count; ++i)
      {
        newPersons[i] = persons[i];
      }

      delete[] persons;
      persons = newPersons;
      capacity = newCapacity;
    }
    persons[count++] = person;
  }

  bool existsPerson(const Person * persons, size_t count, size_t id)
  {
    for (size_t i = 0; i < count; ++i)
    {
      if (persons[i].id == id)
      {
        return true;
      }
    }
    return false;
  }
}
