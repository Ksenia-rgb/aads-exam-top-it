#include "person.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
  zhuravleva::Args args = {"", "", false, false};
  if (!zhuravleva::parseArgs(argc, argv, args))
  {
    std::cerr << "wrong parameters\n";
    return 1;
  }
  std::ifstream inputFile;
  std::istream *input = &std::cin;
  if (args.hasInput)
  {
    inputFile.open(args.inputFile.c_str());
    if (!inputFile.is_open())
    {
      std::cerr << "file open error\n";
      return 2;
    }
    input = &inputFile;
  }

  zhuravleva::DynamicArray< zhuravleva::Person > persons;
  zhuravleva::init(persons);
  size_t good = 0;
  size_t bad = 0;

  try
  {
    zhuravleva::readPersons(*input, persons, good, bad);
  }
  catch (...)
  {
    zhuravleva::destroy(persons);
    std::cerr << "internal error\n";
    return 2;
  }

  std::ofstream outputFile;
  std::ostream *output = &std::cout;

  if (args.hasOutput)
  {
    outputFile.open(args.outputFile.c_str());
    if (!outputFile.is_open())
    {
      zhuravleva::destroy(persons);
      std::cerr << "file open error\n";
      return 2;
    }
    output = &outputFile;
  }

  zhuravleva::printPersons(*output, persons);
  std::cerr << good << " " << bad << "\n";
  zhuravleva::destroy(persons);
  return 0;
}
