#include "options.hpp"
#include "person.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
  const size_t argumentCount = argc;
  muraviev::ProgramOptions options;
  if (!muraviev::parseProgramOptions(argumentCount, argv, options))
  {
    return 1;
  }

  std::ifstream inputFile;
  std::ofstream outputFile;
  std::istream* input = &std::cin;
  std::ostream* output = &std::cout;
  if (options.hasInput)
  {
    inputFile.open(options.inputName);
    if (!inputFile)
    {
      return 2;
    }
    input = &inputFile;
  }
  if (options.hasOutput)
  {
    outputFile.open(options.outputName);
    if (!outputFile)
    {
      return 2;
    }
    output = &outputFile;
  }

  muraviev::PersonList persons;
  muraviev::initList(persons);
  size_t accepted = 0;
  size_t ignored = 0;
  muraviev::readPersons(*input, persons, accepted, ignored);
  muraviev::printPersons(*output, persons);
  std::cerr << accepted << ' ' << ignored << '\n';
  muraviev::clearList(persons);
  return 0;
}
