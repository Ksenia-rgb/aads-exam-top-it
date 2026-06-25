#include "person.hpp"
#include <iostream>
#include <fstream>

namespace nabieva {
  struct ProgramArgs
  {
    const char* inputFile;
    const char* outputFile;
  };

  bool readArgs(int argc, char** argv, ProgramArgs& args)
  {
    args.inputFile = 0;
    args.outputFile = 0;

    if (argc > 3)
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
}

int main(int argc, char** argv)
{
  ProgramArgs args = { 0, 0 };
  if (!readArgs(argc, argv, args))
  {
    return 1;
  }
  std::ifstream inputFile;
  nabieva::PersonStorage storage;
  nabieva::initStorage(storage);
  nabieva::ReadStats stats = { 0, 0 };
}