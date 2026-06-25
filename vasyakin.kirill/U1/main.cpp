#include <iostream>
#include <fstream>
#include <memory>
#include "person.hpp"
#include "array.hpp"
#include "hashtable.hpp"
#include "args.hpp"
#include "parser.hpp"

namespace
{
  void cleanupResources(vasyakin::array< vasyakin::Person >& persons,
    vasyakin::hashTable< size_t >& seen) noexcept
  {
    vasyakin::clearArray(persons);
    vasyakin::clearHashTable(seen);
  }

  bool isBlankLine(const std::string& line) noexcept
  {
    for (char c : line)
    {
      if (!std::isspace(static_cast< unsigned char >(c))) 
      {
        return false;
      }
    }

    return true;
  }
}

int main(int argc, char** argv)
{
  vasyakin::Args args = vasyakin::parseArgs(argc, argv);

  if (!args.valid)
  {
    return 1;
  }

  vasyakin::array< vasyakin::Person > persons = vasyakin::makeArray< vasyakin::Person >(4);
  vasyakin::hashTable< size_t > seen = vasyakin::makeHashTable< size_t >(16);

  size_t successCount = 0;
  size_t ignoreCount = 0;

  try
  {
    {
      std::istream* inStream = std::addressof(std::cin);
      std::ifstream inFile;

      if (args.hasIn)
      {
        inFile.open(args.inFile);
        if (!inFile.is_open())
        {
          cleanupResources(persons, seen);
          return 2;
        }

        inStream = std::addressof(inFile);
      }

      std::string line;
      while (std::getline(*inStream, line))
      {
        if (isBlankLine(line))
        {
          continue;
        }

        vasyakin::Person p;
        if (!vasyakin::parseLine(line, p))
        {
          ++ignoreCount;
          continue;
        }

        if (!vasyakin::insertHashTable(seen, p.id))
        {
          ++ignoreCount;
          continue;
        }

        vasyakin::pushBackArray(persons, p);
        ++successCount;
      }
    }

    {
      std::ostream* outStream = std::addressof(std::cout);
      std::ofstream outFile;

      if (args.hasOut)
      {
        outFile.open(args.outFile);
        if (!outFile.is_open())
        {
          cleanupResources(persons, seen);
          return 2;
        }
        outStream = std::addressof(outFile);
      }

      for (size_t i = 0; i < persons.size; ++i)
      {
        *outStream << persons.data[i].id << " " << persons.data[i].info << "\n";
      }
    }

    std::cerr << successCount << " " << ignoreCount << "\n";

    cleanupResources(persons, seen);

    return 0;
  }
  catch (...)
  {
    cleanupResources(persons, seen);
    return 2;
  }
}
