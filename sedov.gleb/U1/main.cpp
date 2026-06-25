#include "person.hpp"
#include "vector.hpp"
#include "hash_table.hpp"
#include "args.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

namespace
{
  void cleanupResources(sedov::Vector< sedov::Person > & persons, sedov::hashTable< size_t >& seen) noexcept
  {
    sedov::clearVec(persons);
    sedov::clearHashTable(seen);
  }
}

int main(int argc, char ** argv)
{
  if (argc > 3)
  {
    return 1;
  }
  sedov::Args args = sedov::parseArgs(argc, argv);
  if (!args.valid)
  {
    return 1;
  }
  sedov::Vector< sedov::Person > persons = sedov::makeVec< sedov::Person >(4);
  sedov::hashTable< size_t > seen = sedov::makeHashTable< size_t >(16);
  size_t ignoreCount = 0;
  try
  {
    {
      std::istream * inStream = std::addressof(std::cin);
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
      while (std::getline(* inStream, line))
      {
        if (line.empty())
        {
          continue;
        }
        sedov::Person p;
        if (!sedov::parseLine(line, p))
        {
          ++ignoreCount;
          continue;
        }
        if (!sedov::insertHashTable(seen, p.id))
        {
          ++ignoreCount;
          continue;
        }
        sedov::pushBackVec(persons, p);
      }
    }
    {
      std::ostream * outStream = std::addressof(std::cout);
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
        * outStream << persons.data[i].id << " " << persons.data[i].info << "\n";
      }
    }
    std::cerr << persons.size << " " << ignoreCount << "\n";
    cleanupResources(persons, seen);
    return 0;
  }
  catch (...)
  {
    cleanupResources(persons, seen);
    return 2;
  }
}
