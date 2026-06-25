#include "functions.hpp"
#include "Person.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc > 3)
  {
    return 1;
  }

  lachugin::Person* persons = nullptr;
  size_t size = 0;
  size_t capacity = 0;
  std::istream* input = &std::cin;
  std::ostream* output = &std::cout;
  std::ifstream inputFile;
  std::ofstream outputFile;
  std::string outputName;

  bool hasInput = false;
  bool hasOutput = false;

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];
    if (arg.size() >= 3 && arg.substr(0, 3) == "in:")
    {
      if (hasInput)
      {
        return 1;
      }
      inputFile.open(arg.substr(3));
      if (!inputFile)
      {
        return 4;
      }
      input = &inputFile;
      hasInput = true;
    }
    else if (arg.size() >= 4 && arg.substr(0, 4) == "out:")
    {
      if (hasOutput)
      {
        return 1;
      }

      outputName = arg.substr(4);
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
    if (line.empty())
    {
      continue;
    }

    lachugin::Person person;
    if (!lachugin::parseLine(line, person))
    {
      ignored++;
      continue;
    }

    if (lachugin::containsId(persons, size, person.id))
    {
      ignored++;
      continue;
    }

    lachugin::pushBack(persons, size, capacity, person);
    success++;
  }

  if (inputFile.is_open())
  {
    inputFile.close();
  }
  if (hasOutput)
  {
    outputFile.open(outputName);

    if (!outputFile)
    {
      delete[] persons;
      return 2;
    }
    output = &outputFile;
  }

  if (size == 0)
  {
    *output << '\n';
  }
  else
  {
    for (size_t i = 0; i < size; i++)
    {
      *output << persons[i].id << ' ' << persons[i].info << '\n';
    }
  }

  if (success != 0 || ignored != 0)
  {
    std::cerr << success << ' ' << ignored << '\n';
  }
  else
  {
    std::cerr << success << ' ' << ignored << '\n';
  }
  delete[] persons;
  return 0;
}
