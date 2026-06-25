#include <iostream>
#include <fstream>
#include <string>

#include "args.hpp"
#include "parser.hpp"
#include "person.hpp"

int main(int argc, char *argv[])
{
  const studilova::Args args = studilova::parseArgs(argc, argv);

  if (!args.valid_)
  {
    return 1;
  }

  studilova::PersonArray persons;
  studilova::initPersonArray(persons);

  try
  {
    std::ifstream inputFile;
    std::istream* input = &std::cin;

    if (args.hasInput_)
    {
      inputFile.open(args.inputFile_);

      if (!inputFile)
      {
        studilova::destroyPersonArray(persons);
        return 2;
      }

      input = &inputFile;
    }

    std::string line;

    while (std::getline(*input, line))
    {
      studilova::Person person;

      if (studilova::parsePersonLine(line, person) && !studilova::containsPersonId(persons, person.id_))
      {
        studilova::appendPerson(persons, person);
      }
    }

    inputFile.close();

    std::ofstream outputFile;
    std::ostream* output = &std::cout;

    if (args.hasOutput_)
    {
      outputFile.open(args.outputFile_);

      if (!outputFile)
      {
        studilova::destroyPersonArray(persons);
        return 2;
      }
      output = &outputFile;
    }

    for (size_t i = 0; i < persons.size_; ++i)
    {
      *output << persons.data_[i].id_ << ' ' << persons.data_[i].info_ << '\n';
    }

    studilova::destroyPersonArray(persons);
  }
  catch (...)
  {
    studilova::destroyPersonArray(persons);
    return 2;
  }

  return 0;
}
