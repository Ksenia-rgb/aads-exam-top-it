#include "functions.hpp"
#include "Person.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  lachugin::Person* persons = nullptr;
  size_t size = 0;
  size_t capacity = 0;
  std::istream* input = &std::cin;
  std::ostream* output = &std::cout;
  std::ifstream inputFile;
  std::ofstream outputFile;
  bool hasInput = false;
  bool hasOutput = false;

  if (argc > 3)
  {
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];
    if (arg.substr(0, 3) == "in:")
    {
      if (hasInput)
      {
        return 1;
      }
      inputFile.open(arg.substr(3));
      if (!inputFile)
      {
        return 2;
      }
      input = &inputFile;
      hasInput = true;
    }

    else if (arg.substr(0, 4) == "out:")
    {
      if (hasOutput)
      {
        return 1;
      }
      outputFile.open(arg.substr(4));
      if (!outputFile)
      {
        return 2;

      }
      output = &outputFile;
      hasOutput = true;
    }
    else
    {
      return 1;
    }
  }

  size_t success = 0;
  size_t ignored = 0;
  std::string line;
  while (std::getline(*input, line))
  {
    lachugin::Person person;
    if (!parseLine(line, person))
    {
      ignored++;
      continue;
    }

    if (containsId(persons, size, person.id))
    {
      ignored++;
      continue;
    }
    pushBack(persons, size, capacity, person);
    success++;
  }

  for (size_t i = 0; i < size; i++)
  {
    *output << persons[i].id << ' ' << persons[i].info << '\n';
  }

  std::cerr << success << ' ' << ignored << '\n';
  delete[] persons;

}
