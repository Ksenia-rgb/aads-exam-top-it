#include <fstream>
#include <iostream>

#include "list.hpp"
#include "helpedFunc.hpp"


int main(int argc, char* argv[])
{
  std::istream* input = &std::cin;
  std::ifstream inFile;
  std::ifstream dataFile;
  std::string inFilename;
  std::string dataFilename;

  int inCount = 0;
  int dataCount = 0;

  donkeev::PersonList persons;
  persons.head_ = nullptr;
  persons.tail_ = nullptr;
  persons.size_ = 0;

  if (argc > 3)
  {
    std::cerr << "Bad parametrs\n";
    return 1;
  }


  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    
    if (arg.rfind("in:", 0) == 0)
    {
      ++inCount;
      if (inCount > 1)
      {
        std::cerr << "Invalid arguments: multiple input files specified\n";
        return 1;
      }
      
      inFilename = arg.substr(3);
      if (inFilename.empty())
      {
        std::cerr << "Invalid arguments: empty filename for input\n";
        return 1;
      }
    }
    else if (arg.rfind("data:", 0) == 0)
    {
        ++dataCount;
        if (dataCount > 1)
        {
          std::cerr << "Invalid arguments: multiple data files specified\n";
          return 1;
        }
        
        dataFilename = arg.substr(5);
        if (dataFilename.empty())
        {
          std::cerr << "Invalid arguments: empty filename for data\n";
          return 1;
        }
    }
    else
    {
      std::cerr << "Invalid arguments: unknown argument '" << arg << "'\n";
      return 1;
    }
  }

  if (dataCount == 0)
  {
    std::cerr << "Invalid arguments: missing required 'data:' argument\n";
    return 1;
  }
    
  if (!inFilename.empty())
  {
    inFile.open(inFilename);
    if (!inFile.is_open())
    {
      std::cerr << "Failed to open input file: " << inFilename << "\n";
      return 2;
    }
    input = &inFile;
  }
  
  if (!inFilename.empty())
  {
    inFile.open(inFilename);
    if (!inFile.is_open())
    {
      std::cerr << "Failed to open input file: " << inFilename << "\n";
      return 2;
    }
    input = &inFile;
    
    size_t ignoredCount = 0;
    donkeev::readingPersons(*input, persons, ignoredCount);
    
    inFile.close();
  }

  dataFile.open(dataFilename);
  if (!dataFile.is_open())
  {
    std::cerr << "Failed to open data file: " << dataFilename << "\n";
    return 2;
  }
}

