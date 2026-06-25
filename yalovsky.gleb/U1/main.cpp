#include <iostream>
#include <fstream>
#include <string>

#include "Person.hpp"
#include "Array.hpp"

namespace yalovsky
{
  namespace
  {
    const int statusOk = 0;
    const int statusBadArgs = 1;
    const int statusOpenError = 2;

    bool startsWith(const std::string& text, const std::string& prefix)
    {
      if (text.size() < prefix.size())
      {
        return false;
      }
      return text.compare(0, prefix.size(), prefix) == 0;
    }
  }
}

int main(int argc, char** argv)
{
  const std::string inPrefix = "in:";
  const std::string outPrefix = "out:";
  std::string inputName;
  std::string outputName;
  bool hasInput = false;
  bool hasOutput = false;
  const int maxArguments = 2;
  if (argc - 1 > maxArguments)
  {
    std::cerr << "invalid arguments" << '\n';
    return yalovsky::statusBadArgs;
  }
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg = argv[i];
    if (yalovsky::startsWith(arg, inPrefix))
    {
      if (hasInput)
      {
        std::cerr << "invalid arguments" << '\n';
        return yalovsky::statusBadArgs;
      }
      hasInput = true;
      inputName = arg.substr(inPrefix.size());
    }
    else if (yalovsky::startsWith(arg, outPrefix))
    {
      if (hasOutput)
      {
        std::cerr << "invalid arguments" << '\n';
        return yalovsky::statusBadArgs;
      }
      hasOutput = true;
      outputName = arg.substr(outPrefix.size());
    }
    else
    {
      std::cerr << "invalid arguments" << '\n';
      return yalovsky::statusBadArgs;
    }
  }

  yalovsky::Array< yalovsky::Person > persons = yalovsky::makeArray< yalovsky::Person >();
  size_t accepted = 0;
  size_t ignored = 0;
  try
  {
    if (hasInput)
    {
      std::ifstream input(inputName);
      if (!input.is_open())
      {
        yalovsky::freeArray(persons);
        std::cerr << "cannot open file" << '\n';
        return yalovsky::statusOpenError;
      }
      yalovsky::readPersons(input, persons, accepted, ignored);
    }
    else
    {
      yalovsky::readPersons(std::cin, persons, accepted, ignored);
    }

    if (hasOutput)
    {
      std::ofstream output(outputName);
      if (!output.is_open())
      {
        yalovsky::freeArray(persons);
        std::cerr << "cannot open file" << '\n';
        return yalovsky::statusOpenError;
      }
      yalovsky::printPersons(output, persons);
    }
    else
    {
      yalovsky::printPersons(std::cout, persons);
    }
  }
  catch (...)
  {
    yalovsky::freeArray(persons);
    std::cerr << "internal error" << '\n';
    return yalovsky::statusOpenError;
  }

  std::cerr << accepted << ' ' << ignored << '\n';
  yalovsky::freeArray(persons);
  return yalovsky::statusOk;
}
