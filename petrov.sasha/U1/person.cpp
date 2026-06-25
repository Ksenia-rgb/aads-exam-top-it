#include "person.hpp"

#include <new>
#include <cctype>
#include <stdexcept>

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

  bool isDuplicate(const personArr* array, const size_t id)
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

  bool parseLine(const std::string& line, Person& person)
  {
    size_t pos = 0;
    while (pos < line.length() && std::isspace(static_cast<unsigned char>(line[pos])))
    {
      ++pos;
    }
    if (pos == line.length() || !std::isdigit(static_cast<unsigned char>(line[pos])))
    {
      return false;
    }
    size_t endPos = 0;
    size_t id = 0;
    try
    {
      id = std::stoull(line.substr(pos), &endPos);
    }
    catch (...)
    {
      return false;
    }
    pos += endPos;
    if (pos < line.length() && !std::isspace(static_cast<unsigned char>(line[pos])))
    {
      return false;
    }

    while (pos < line.length() && std::isspace(static_cast<unsigned char>(line[pos])))
    {
      ++pos;
    }
    if (pos == line.length())
    {
      return false;
    }
    person.id = id;
    person.info = line.substr(pos);
    return true;
  }

  void readPersons(std::istream& inStream, personArr* persons, size_t& successCount, size_t& ignoredCount)
  {
    std::string line = "";
    while (std::getline(inStream, line))
    {
      bool isEmpty = true;
      for (size_t i = 0; i < line.length(); ++i)
      {
        if (!std::isspace(static_cast<unsigned char>(line[i])))
        {
          isEmpty = false;
          break;
        }
      }
      if (isEmpty)
      {
        continue;
      }

      Person currentPerson = {};
      if (parseLine(line, currentPerson))
      {
        if (isDuplicate(persons, currentPerson.id))
        {
          ++ignoredCount;
        }
        else
        {
          pushPerson(persons, currentPerson);
          ++successCount;
        }
      }
      else
      {
        ++ignoredCount;
      }
    }
    if (inStream.bad())
    {
      return;
    }
  }

  void writePersons(std::ostream& outStream, const personArr* persons)
  {
    for (size_t i = 0; i < persons->size; ++i)
    {
      outStream << persons->data[i].id << ' ' << persons->data[i].info << '\n';
    }
  }
}
