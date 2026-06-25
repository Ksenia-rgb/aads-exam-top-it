#include "person.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

namespace nabieva {
  struct ProgramArgs
  {
    const char* inputFile;
    const char* outputFile;
  };

  bool startsWith(const char* value, const char* prefix)
  {
    while (*prefix != '\0')
    {
      if (*value != *prefix)
      {
        return false;
      }
      ++value;
      ++prefix;
    }
    return true;
  }

  bool readArgs(int argc, char** argv, ProgramArgs& args)
  {
    args.inputFile = 0;
    args.outputFile = 0;

    if (argc > 4)
    {
      return false;
    }

    for (int i = 1; i < argc; ++i)
    {
      if (startsWith(argv[i], "in:"))
      {
        if (args.inputFile != 0 || argv[i][3] == '\0')
        {
          return false;
        }
        args.inputFile = argv[i] + 3;
      }
      else if (startsWith(argv[i], "out:"))
      {
        if (args.outputFile != 0 || argv[i][4] == '\0')
        {
          return false;
        }
        args.outputFile = argv[i] + 4;
      }
      else
      {
        return false;
      }
    }

    return true;
  }
}

int main(int argc, char** argv)
{
  nabieva::ProgramArgs args = { 0, 0 };
  if (!readArgs(argc, argv, args))
  {
    return 1;
  }
  std::ifstream inputFile;
  nabieva::PersonStorage storage;
  nabieva::initStorage(storage);
  nabieva::ReadStats stats = { 0, 0 };
  std::istream* input = &std::cin;
  if (args.inputFile != 0)
  {
    inputFile.open(args.inputFile);
    if (!inputFile)
    {
      nabieva::destroyStorage(storage);
      return 2;
    }
    input = &inputFile;
  }

  if (!nabieva::readPersons(*input, storage, stats))
  {
    nabieva::destroyStorage(storage);
    return 2;
  }

  std::ofstream outputFile;
  std::ostream* output = &std::cout;

  if (args.outputFile != 0)
  {
    outputFile.open(args.outputFile);
    if (!outputFile)
    {
      nabieva::destroyStorage(storage);
      return 2;
    }
    output = &outputFile;
  }

  nabieva::printPersons(*output, storage);
  if (stats.accepted != 0 || stats.ignored != 0)
  {
    std::cerr << stats.accepted << ' ' << stats.ignored;
  }
  std::cout << '\n';

  nabieva::destroyStorage(storage);
}
