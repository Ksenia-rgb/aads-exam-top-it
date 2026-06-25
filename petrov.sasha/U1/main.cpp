#include "person.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <new>

namespace petrov
{
  const size_t INITIAL_CAPACITY = 16;
}

namespace
{
  bool parseArgs(int argc, char* argv[], std::string& inFile, std::string& outFile)
  {
    if (argc > 3)
    {
      return false;
    }
    bool hasIn = false;
    bool hasOut = false;
    for (int i = 1; i < argc; ++i)
    {
      std::string arg = argv[i];
      if (arg.find("in:") == 0)
      {
        if (hasIn)
        {
          return false;
        }
        hasIn = true;
        inFile = arg.substr(3);
      }
      else if (arg.find("out:") == 0)
      {
        if (hasOut)
        {
          return false;
        }
        hasOut = true;
        outFile = arg.substr(4);
      }
      else
      {
        return false;
      }
    }
    return true;
  }
}

int main(int argc, char* argv[])
{
  try
  {
    std::string inFilename = "";
    std::string outFilename = "";
    if (!parseArgs(argc, argv, inFilename, outFilename))
    {
      std::cerr << "Invalid command line arguments\n";
      return 1;
    }

    std::istream* inStream = &std::cin;
    std::ifstream inFile;
    if (!inFilename.empty())
    {
      inFile.open(inFilename);
      if (!inFile.is_open())
      {
        std::cerr << "Cannot open input file\n";
        return 2;
      }
      inStream = &inFile;
    }

    petrov::personArr* persons = nullptr;
    size_t successCount = 0;
    size_t ignoredCount = 0;

    try
    {
      persons = petrov::createPersonArray(petrov::INITIAL_CAPACITY);
      petrov::readPersons(*inStream, persons, successCount, ignoredCount);
    }
    catch (...)
    {
      petrov::destroyPersonArray(persons);
      throw;
    }

    if (!inFilename.empty())
    {
      inFile.close();
    }

    std::ostream* outStream = &std::cout;
    std::ofstream outFile;
    if (!outFilename.empty())
    {
      outFile.open(outFilename);
      if (!outFile.is_open())
      {
        petrov::destroyPersonArray(persons);
        std::cerr << "Cannot open output file\n";
        return 2;
      }
      outStream = &outFile;
    }

    try
    {
      petrov::writePersons(*outStream, persons);
    }
    catch (...)
    {
      petrov::destroyPersonArray(persons);
      throw;
    }

    if (!outFilename.empty())
    {
      outFile.close();
    }

    petrov::destroyPersonArray(persons);
    if (successCount != 0 || ignoredCount != 0)
    {
      std::cerr << successCount << " " << ignoredCount << '\n';
    }
    return 0;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Bad Allocation\n";
    return 2;
  }
  catch (const std::runtime_error&)
  {
    std::cerr << "Runtime Error\n";
    return 2;
  }
  catch (const std::exception&)
  {
    std::cerr << "Exception\n";
    return 2;
  }
}
