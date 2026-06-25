#include <iostream>
#include <string>
#include <sstream>

struct Person
{
  size_t id;
  std::string info;
};

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

int main()
{
  Person* persons = nullptr;
  size_t count = 0;
  size_t capacity = 0;
  size_t ignored = 0;
  std::string line;

  while (std::getline(std::cin, line))
  {
    Person person;
    if (parseLine(line, person))
    {
      if (!existsPerson(persons, count, person.id))
      {
        addPerson(persons, count, capacity, person);
      }
      else
      {
        ++ignored;
      }
    }
    else
    {
      ++ignored;
    }
  }

  for (size_t i = 0; i < count; ++i)
  {
    std::cout << persons[i].id << ' ' << persons[i].info << '\n';
  }

  std::cerr << count << ' ' << ignored << '\n';

  delete[] persons;
  return 0;
}
