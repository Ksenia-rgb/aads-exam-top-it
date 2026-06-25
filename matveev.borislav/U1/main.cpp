#include <iostream>

#include "array.hpp"
#include "person.hpp"

int main()
{
  matveev::Array< matveev::Person > people;
  size_t validCount = 0;
  size_t ignoredCount = 0;

  matveev::Person person;
  bool valid = false;
  while (matveev::readPerson(std::cin, person, valid))
  {
    if (valid)
    {
      bool duplicate = false;
      for (size_t i = 0; i < people.size; ++i)
      {
        if (people.data[i].id == person.id)
        {
          duplicate = true;
          break;
        }
      }
      if (duplicate)
      {
        ++ignoredCount;
      }
      else
      {
        matveev::pushBack(people, person);
        ++validCount;
      }
    }
    else
    {
      ++ignoredCount;
    }
  }

  for (size_t i = 0; i < people.size; ++i)
  {
    matveev::writePerson(std::cout, people.data[i]);
    std::cout << '\n';
  }
  std::cerr << validCount << ' ' << ignoredCount << '\n';

  return 0;
}
