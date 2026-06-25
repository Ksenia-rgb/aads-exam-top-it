#include <iostream>
#include <string>
#include <fstream>
#include <hashtable.hpp>

namespace
{
  std::istream& skipSpaces(std::istream& is)
  {
    while (is.peek() == ' ')
    {
      is.get();
    }
    return is;
  }
  bool isEOL(std::istream& is)
  {
    if (is.peek() == '\n' || is.peek() == EOF)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

namespace goltsov
{
  std::pair< size_t, size_t > readPersons(HashTable& ht, std::istream& is, List** l)
  {
    size_t id;
    std::string info;
    List* start_l = *l;
    size_t good = 0, bad = 0;
    while (is)
    {
      if (is >> id)
      {
        skipSpaces(is);
        if (!isEOL(is))
        {
          is >> info;
          try
          {
            insertPerson(ht, id, {id, info});
            ++good;
            if (*l)
            {
              (*l)->next = newListNode(id, {id, info}, *l, nullptr);
              (*l) = (*l)->next;
            }
            else
            {
              *l = newListNode(id, {id, info}, *l, nullptr);
              start_l = *l;
            }
          }
          catch (...)
          {
            ++bad;
          }
        }
      }
      else
      {
        if (!is.eof())
        {
          is.clear();
        }
      }
    }
    *l = start_l;
    return {good, bad};
  }
}

int main(int argc, char** argv)
{
  std::fstream inFile;
  std::fstream dataFile;
  std::string dataFilename;
  std::istream* is = &std::cin;
  std::istream* ds = &std::cin;
  std::ostream* os = &std::cout;
  if (argc > 3)
  {
    std::cerr << "Many args\n";
    return 0;
  }
  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.substr(0, 3) == "in:" && is == &std::cin)
    {
      std::string filename = arg.substr(3);
      inFile.open(filename);
      if (!inFile.is_open())
      {
        std::cerr << "Cannot open input file\n";
        return 2;
      }
      is = &inFile;
    }
    else if (arg.substr(0, 5) == "data:" && dataFilename.empty())
    {
      dataFilename = arg.substr(5);
      dataFile.open(dataFilename);
      if (!dataFile.is_open())
      {
        std::cerr << "Cannot open data file\n";
        return 2;
      }
      ds = &dataFile;
    }
    else
    {
      std::cerr << "Invalid argument: " << arg << '\n';
      return 1;
    }
  }
  if (dataFilename.empty())
  {
    std::cerr << "Invalid arguments: no data file\n";
    return 1;
  }
  goltsov::HashTable ht = goltsov::newHT(100);
  goltsov::List* l = nullptr;
  std::pair< size_t, size_t > res = goltsov::readPersons(ht, *is, &l);
  if (!outFilename.empty())
  {
    outFile.open(outFilename, std::ios::trunc);
    if (!outFile.is_open())
    {
      std::cerr << "Cannot open output file\n";
      return 2;
    }
    os = &outFile;
  }
  goltsov::printRes(*os, l);
  *os << '\n';
  std::cerr << res.first << ' ' << res.second << '\n';
  goltsov::deleteHashTable(ht);
  goltsov::deleteList(l);
}
