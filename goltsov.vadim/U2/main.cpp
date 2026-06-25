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
  std::pair< size_t, size_t > readPersons(HashTable< Person >& ht, std::istream& is, List< Person >** l)
  {
    size_t id;
    std::string info;
    List< Person >* start_l = *l;
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
            insertToHT(ht, id, {id, info});
            ++good;
            if (*l)
            {
              (*l)->next = newListNode< Person >(id, {id, info}, *l, nullptr);
              (*l) = (*l)->next;
            }
            else
            {
              *l = newListNode< Person >(id, {id, info}, *l, nullptr);
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

  void readData(std::istream& ds, HashTable< Meet_arr >& ht_meet)
  {
    size_t id_from, id_to, length;
    while (ds >> id_from >> id_to >> length)
    {
      try
      {
        List< Meet >* m = getFromHT(ht_meet, id_from).data;
      }
    }
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
  goltsov::HashTable< goltsov::Person > ht = goltsov::newHT< goltsov::Person >(100);
  goltsov::List< goltsov::Person >* l = nullptr;
  std::pair< size_t, size_t > res = goltsov::readPersons(ht, *is, &l);

  goltsov::HashTable< goltsov::Meet_arr > ht_meets = goltsov::newHT< goltsov::Meet_arr >(100);

  goltsov::deleteHashTable(ht);
  goltsov::deleteList(l);
}
