#include <fstream>
#include <iostream>
#include <string>

#include "args.hpp"
#include "array.hpp"
#include "hashtable.hpp"
#include "parser.hpp"
#include "person.hpp"

namespace
{

  struct ReadStats
  {
    size_t accepted;
    size_t ignored;
  };

  ReadStats readInto(std::istream& in, burukov::darray< burukov::Person >& persons)
  {
    burukov::hashTable< size_t > seen = burukov::makeHashTable< size_t >(16);
    ReadStats stats{0, 0};
    std::string line;
    try
    {
      while (std::getline(in, line))
      {
        burukov::Person p{0, ""};
        burukov::ParseResult pr = burukov::parseLine(line, p);
        if (pr == burukov::PARSE_BLANK)
        {
          continue;
        }
        if (pr == burukov::PARSE_INVALID)
        {
          ++stats.ignored;
        }
        else if (!burukov::insertHashTable(seen, p.id))
        {
          ++stats.ignored;
        }
        else
        {
          burukov::pushBackArray(persons, std::move(p));
          ++stats.accepted;
        }
      }
    }
    catch (...)
    {
      burukov::clearHashTable(seen);
      throw;
    }
    burukov::clearHashTable(seen);
    return stats;
  }

  void writeAll(std::ostream& out, const burukov::darray< burukov::Person >& persons)
  {
    for (size_t i = 0; i < persons.size; ++i)
    {
      out << persons.data[i].id << " " << persons.data[i].info << "\n";
    }
  }

  int run(const burukov::Args& args, burukov::darray< burukov::Person >& persons)
  {
    std::ifstream inFile;
    if (args.hasIn)
    {
      inFile.open(args.inFile);
      if (!inFile.is_open())
      {
        std::cerr << "Cannot open input file" << "\n";
        return 2;
      }
    }
    std::istream& in = args.hasIn ? static_cast< std::istream& >(inFile) : std::cin;
    ReadStats stats = readInto(in, persons);
    inFile.close();
    std::ofstream outFile;
    if (args.hasOut)
    {
      outFile.open(args.outFile);
      if (!outFile.is_open())
      {
        std::cerr << "Cannot open output file" << "\n";
        return 2;
      }
    }
    std::ostream& out = args.hasOut ? static_cast< std::ostream& >(outFile) : std::cout;
    if (persons.size > 0)
    {
      writeAll(out, persons);
    }
    writeAll(out, persons);
    std::cerr << stats.accepted << " " << stats.ignored << "\n";
    return 0;
  }

}

int main(int argc, char** argv)
{
  burukov::Args args = burukov::parseArgs(argc, argv);
  if (!args.valid)
  {
    std::cerr << "Invalid arguments" << "\n";
    return 0;
  }
  burukov::darray< burukov::Person > persons = burukov::makeArray< burukov::Person >(4);
  int code = 0;
  try
  {
    code = run(args, persons);
  }
  catch (...)
  {
    burukov::clearArray(persons);
    throw;
  }
  burukov::clearArray(persons);
  return code;
}
