#include <iostream>
#include <fstream>
#include <string>
#include "person.hpp"
#include "list.hpp"

int main(int argc, char* argv[])
{
  std::string inputFile;
  std::string outputFile;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg.rfind("in:", 0) == 0)
    {
      if (!inputFile.empty())
      {
        std::cerr << "Error: duplicate input file argument\n";
        return 1;
      }
      inputFile = arg.substr(3);
    }
    else if (arg.rfind("out:", 0) == 0)
    {
      if (!outputFile.empty())
      {
        std::cerr << "Error: duplicate output file argument\n";
        return 1;
      }
      outputFile = arg.substr(4);
    }
    else
    {
      std::cerr << "Error: invalid argument\n";
      return 1;
    }
  }

  std::istream* in = &std::cin;
  std::ifstream inputFileStream;

  if (!inputFile.empty())
  {
    inputFileStream.open(inputFile);
    if (!inputFileStream.is_open())
    {
      std::cerr << "Error: cannot open input file\n";
      return 2;
    }
    in = &inputFileStream;
  }

  std::ostream* out = &std::cout;
  std::ofstream outputFileStream;

  if (!outputFile.empty())
  {
    outputFileStream.open(outputFile);
    if (!outputFileStream.is_open())
    {
      std::cerr << "Error: cannot open output file\n";
      return 2;
    }
    out = &outputFileStream;
  }

  vishnyakov::List< vishnyakov::Person > persons;
  std::string line;

  while (std::getline(*in, line))
  {
    *out << line << "\n";
  }

  return 0;
}

