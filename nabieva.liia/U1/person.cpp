#include "person.hpp"

#include <istream>
#include <limits>
#include <new>
#include <ostream>

namespace
{
  bool isSpace(char symbol)
  {
    return symbol == ' ' || symbol == '\t' || symbol == '\v' || symbol == '\f' || symbol == '\r';
  }

  void skipSpaces(const std::string& line, std::size_t& position)
  {
    while (position < line.size() && isSpace(line[position]))
    {
      ++position;
    }
  }

  bool readId(const std::string& line, std::size_t& position, std::size_t& id)
  {
    skipSpaces(line, position);
    if (position == line.size() || line[position] < '0' || line[position] > '9')
    {
      return false;
    }

    id = 0;
    while (position < line.size() && line[position] >= '0' && line[position] <= '9')
    {
      const std::size_t digit = static_cast<std::size_t>(line[position] - '0');
      if (id > (std::numeric_limits< std::size_t >::max() - digit) / 10)
      {
        return false;
      }
      id = id * 10 + digit;
      ++position;
    }
    return true;
  }

  bool hasId(const nabieva::PersonStorage& storage, std::size_t id)
  {
    for (std::size_t i = 0; i < storage.size; ++i)
    {
      if (storage.data[i].id == id)
      {
        return true;
      }
    }
    return false;
  }

  bool reserve(nabieva::PersonStorage& storage, std::size_t capacity)
  {
    nabieva::Person* newData = new (std::nothrow) nabieva::Person[capacity];
    if (newData == 0)
    {
      return false;
    }

    for (std::size_t i = 0; i < storage.size; ++i)
    {
      newData[i] = storage.data[i];
    }

    delete[] storage.data;
    storage.data = newData;
    storage.capacity = capacity;
    return true;
  }

  bool pushBack(nabieva::PersonStorage& storage, const nabieva::Person& person)
  {
    if (storage.size == storage.capacity)
    {
      if (storage.capacity > std::numeric_limits< std::size_t >::max() / 2)
      {
        return false;
      }
      const std::size_t newCapacity = storage.capacity == 0 ? 4 : storage.capacity * 2;
      if (!reserve(storage, newCapacity))
      {
        return false;
      }
    }

    storage.data[storage.size] = person;
    ++storage.size;
    return true;
  }
}

void nabieva::initStorage(PersonStorage& storage)
{
  storage.data = 0;
  storage.size = 0;
  storage.capacity = 0;
}

void nabieva::destroyStorage(PersonStorage& storage)
{
  delete[] storage.data;
  storage.data = 0;
  storage.size = 0;
  storage.capacity = 0;
}

bool nabieva::readPersons(std::istream& input, PersonStorage& storage, ReadStats& stats)
{
  stats.accepted = 0;
  stats.ignored = 0;

  std::string line;
  while (std::getline(input, line))
  {
    std::size_t position = 0;
    skipSpaces(line, position);

    if (position == line.size())
    {
      continue;
    }

    std::size_t id = 0;
    if (!readId(line, position, id))
    {
      ++stats.ignored;
      continue;
    }

    skipSpaces(line, position);
    if (position == line.size())
    {
      ++stats.ignored;
      continue;
    }

    if (hasId(storage, id))
    {
      ++stats.ignored;
      continue;
    }

    Person person = { id, line.substr(position) };
    if (!pushBack(storage, person))
    {
      return false;
    }

    ++stats.accepted;
  }

  return true;
}

void nabieva::printPersons(std::ostream& output, const PersonStorage& storage)
{
  for (std::size_t i = 0; i < storage.size; ++i)
  {
    output << storage.data[i].id << ' ' << storage.data[i].info << '\n';
  }
}
