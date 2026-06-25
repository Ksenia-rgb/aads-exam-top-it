#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "args.hpp"
#include "parser.hpp"
#include "person.hpp"

namespace
{
  bool isEmptyLine(const std::string &line)
  {
    for (std::size_t i = 0; i < line.size(); ++i)
    {
      if (!std::isspace(static_cast< unsigned char >(line[i])))
      {
        return false;
      }
    }
    return true;
  }
}

int main(int argc, char *argv[])
{
  studilova::PersonArray persons;
  studilova::initPersonArray(persons);

  if (argc > 3)
  {
    std::cerr << "Invalid arguments\n";
    studilova::destroyPersonArray(persons);
    return 0;
  }

  const studilova::Args args = studilova::parseArgs(argc, argv);

  if (!args.valid_)
  {
    std::cerr << "Invalid arguments\n";
    studilova::destroyPersonArray(persons);
    return 1;
  }

  std::ifstream inputFile;
  std::istream* input = &std::cin;

  if (args.hasInput_)
  {
    inputFile.open(args.inputFile_);

    if (!inputFile)
    {
      std::cerr << "Cannot open file\n";
      studilova::destroyPersonArray(persons);
      return 2;
    }
    input = &inputFile;
  }

  size_t count = 0;
  size_t ignore = 0;
  std::string line;

  while (std::getline(*input, line))
  {
    if (isEmptyLine(line))
    {
      continue;
    }

    studilova::Person person;

    if (studilova::parsePersonLine(line, person) && !studilova::containsPersonId(persons, person.id_))
    {
      studilova::appendPerson(persons, person);
      ++count;
    }
    else
    {
      ++ignore;
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
      std::cerr << "Cannot open file\n";
      studilova::destroyPersonArray(persons);
      return 2;
    }
    output = &outputFile;
  }

  for (size_t i = 0; i < persons.size_; ++i)
  {
    *output << persons.data_[i].id_ << ' ' << persons.data_[i].info_ << '\n';
  }

  if (persons.size_ == 0)
  {
    *output << '\n';
  }

  std::cerr << count << ' ' << ignore << '\n';

  studilova::destroyPersonArray(persons);

  return 0;
}
