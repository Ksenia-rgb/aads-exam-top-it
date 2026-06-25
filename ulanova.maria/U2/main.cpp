#include "../common/io.hpp"
#include "../common/parse.hpp"
#include "meet.hpp"
#include "commands.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char * argv[])
{
  std::string inFile;
  std::string dataFile;
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
    else if (arg.size() > 5 && std::string(arg.begin(), arg.begin() + 5) == "data:")
    {
      if (!dataFile.empty())
      {
        std::cerr << "Duplicate data file argument\n";
        return 1;
      }
      dataFile = std::string(arg.begin() + 5, arg.end());
    }
    else
    {
      std::cerr << "Unknown argument: " << arg << "\n";
      return 1;
    }
  }
  if (dataFile.empty())
  {
    std::cerr << "Data file is required\n";
    return 1;
  }

  ulanova::Array< ulanova::Person > persons = ulanova::mArray< ulanova::Person >();
  if (!inFile.empty())
  {
    std::ifstream fin(inFile);
    if (!fin.is_open())
    {
      std::cerr << "Cannot open input file: " << inFile << "\n";
      return 2;
    }
    ulanova::ParseResult result = ulanova::readPersons(fin);
    persons = result.persons;
  }

  std::ifstream dataIn(dataFile);
  if (!dataIn.is_open())
  {
    std::cerr << "Cannot open data file: " << dataFile << "\n";
    ulanova::clear(persons);
    return 2;
  }

  ulanova::Array< ulanova::Meet > meets = ulanova::readMeets(dataIn);
  if (meets.data == nullptr && meets.size == 0 && meets.capacity == 0)
  {
    std::cerr << "Invalid meet data\n";
    ulanova::clear(persons);
    return 3;
  }

  ulanova::runCommands(persons, meets, std::cin, std::cout);

  ulanova::clear(persons);
  ulanova::clear(meets);
  return 0;
}
