#include "io.hpp"
#include "parse.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char * argv[])
{
  if (argc > 3)
  {
    std::cerr << "Too many arguments\n";
    return 0;
  }

  std::string inFile;
  std::string outFile;
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);
    if (arg.size() > 3 && std::string(arg.begin(), arg.begin() + 3) == "in:")
    {
      if (!inFile.empty())
      {
        std::cerr << "Duplicate input file argument\n";
        return 1;
      }
      inFile = std::string(arg.begin() + 3, arg.end());
    }
    else if (arg.size() > 4 && std::string(arg.begin(), arg.begin() + 4) == "out:")
    {
      if (!outFile.empty())
      {
        std::cerr << "Duplicate output file argument\n";
        return 1;
      }
      outFile = std::string(arg.begin() + 4, arg.end());
    }
    else
    {
      std::cerr << "Unknown argument: " << arg << "\n";
      return 1;
    }
  }

  std::ifstream fin;
  if (!inFile.empty())
  {
    fin.open(inFile);
    if (!fin.is_open())
    {
      std::cerr << "Cannot open input file: " << inFile << "\n";
      return 2;
    }
  }

  std::istream & in = inFile.empty() ? std::cin : static_cast< std::istream & >(fin);
  ulanova::ParseResult result = ulanova::readPersons(in);
  fin.close();

  std::ofstream fout;
  if (!outFile.empty())
  {
    fout.open(outFile);
    if (!fout.is_open())
    {
      std::cerr << "Cannot open output file: " << outFile << "\n";
      ulanova::clear(result.persons);
      return 2;
    }
  }

  std::ostream & out = outFile.empty() ? std::cout : static_cast< std::ostream & >(fout);

  ulanova::printPersons(result.persons, out);
  if (result.persons.size == 0)
  {
    out << "\n";
  }
  std::cerr << result.accepted << " " << result.ignored << "\n";
  ulanova::clear(result.persons);
  return 0;
}
