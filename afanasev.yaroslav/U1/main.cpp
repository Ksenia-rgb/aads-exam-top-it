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

int main()
{
  Person * persons = nullptr;
  size_t count = 0;


  persons = nullptr;
  size_t capacity = 0;
  std::string line;

  while (std::getline(std::cin, line))
  {
    Person person;
    if (parseLine(line, person))
    {
      addPerson(persons, count, capacity, person);
    }
  }


  return 0;
}
