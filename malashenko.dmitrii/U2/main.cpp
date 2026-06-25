#include <iostream>
#include <fstream>
#include <vector.hpp>
#include <person.hpp>
#include <common_funcs.hpp>
#include "solution.hpp"

int main(int argc, char ** argv)
{
  using namespace malashenko;
  if (argc > 3)
  {
    std::cerr << "Wrong amount of parameters";
    return 0;
  }
  std::string in_file;
  std::string data_file;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.size() >= 3 && arg.substr(0, 3) == "in:")
    {
      if (!in_file.empty())
      {
        std::cerr << "Can't be 2 input files\n";
        return 1;
      }

      in_file = arg.substr(3);

      if (in_file.empty())
      {
        std::cerr << "Wrong name for input file\n";
        return 1;
      }

    }
    else if (arg.size() >= 4 && arg.substr(0, 5) == "data:")
    {
      if (!data_file.empty())
      {
        std::cerr << "Can't be 2 data files\n";
      }

      data_file = arg.substr(5);

      if (data_file.empty())
      {
        std::cerr << "Wrong name for data file\n";
        return 1;
      }
    }
    else
    {
      std::cerr << "Unknown parametr\n";
      return 1;
    }
  }

  if (data_file.empty())
  {
    std::cerr << "There's no data file\n";
    return 1;
  }

  Vec< std::pair< Person, Person > > daters;
  Vec< size_t > dateDur;
  Vec< Person > persons;

  try
  {
    init(daters, 8);
    init(dateDur, 8);
    init(persons, 8);
  }
  catch(...)
  {
    destroy(daters);
    destroy(dateDur);
    destroy(persons);
    throw;
  }

  std::ifstream in_fs;
  if (!in_file.empty())
  {
    in_fs.open(in_file);
    if (!in_fs)
    {
      std::cerr << "Can't open the input file\n";
      return 2;
    }

    readPersonsData(in_fs, persons);
  }







}
