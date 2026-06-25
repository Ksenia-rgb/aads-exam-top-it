#include "functions.hpp"
#include "Person.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  lachugin::Person* persons = nullptr;
  size_t size = 0;
  size_t capacity = 0;
  std::ifstream inputFile;
  std::ofstream outputFile;
  std::istream* input = &std::cin;
  std::ostream* output = &std::cout;
  std::string inputName;
  std::string outputName;

  size_t inputCount = 0;
  size_t outputCount = 0;

  if (argc > 3)
  {
    std::cerr << "Too many args\n";
    return 0;
  }

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.find("in:") == 0)
    {
      inputName = arg.substr(3);
      ++inputCount;
    }
    else if (arg.find("out:") == 0)
    {
      outputName = arg.substr(4);
      ++outputCount;
    }
    else
    {
      return 1;
    }
  }

  if (inputCount > 1 || outputCount > 1)
  {
    return 1;
  }
  if (inputCount == 1)
  {
    inputFile.open(inputName);
    if (!inputFile)
    {
      std::cerr << "Cant open file\n";
      return 2;
    }
    input = &inputFile;
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
      ++ignored;
      continue;
    }
    if (lachugin::containsId(persons, size, person.id))
    {
      ++ignored;
      continue;
    }

    lachugin::pushBack(persons, size, capacity, person);
    ++success;
  }

  inputFile.close();

  if (outputCount == 1)
  {
    outputFile.open(outputName);

    if (!outputFile)
    {
      delete[] persons;
      std::cerr << "Cant open file\n";
      return 2;
    }
    output = &outputFile;
  }
  for (size_t i = 0; i < size; ++i)
  {
    *output << persons[i].id << ' ' << persons[i].info << '\n';
  }

  if (size == 0)
  {
    *output << '\n';
  }

  std::cerr << success << ' ' << ignored << '\n';
  delete[] persons;
  return 0;
}
