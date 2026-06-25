#include <iostream>

struct Person
{
  size_t id;
  std::string info;
};

int main()
{
  Person * persons = nullptr;
  size_t count = 0;


  persons = nullptr;
  size_t capacity = 0;
  std::string line;
  while (std::getline(in, line))
  {
    Person person;
    if (parseLine(line, person))
    {
            addPerson(persons, count, capacity, person);
    }
  }



  return 0;
}
