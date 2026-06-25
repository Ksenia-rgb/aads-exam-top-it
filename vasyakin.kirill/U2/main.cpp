#include <fstream>
#include <iostream>
#include <string>
#include "args.hpp"
#include "commands.hpp"
#include "loader.hpp"
#include "model.hpp"

namespace
{
  struct Arguments
  {
    std::string personsFile;
    std::string dataFile;
    bool hasPersons;
    bool hasData;
    bool valid;
  };

  Arguments parseArguments(int argc, char** argv)
  {
    Arguments result{ std::string(), std::string(), false, false, true };

    if (argc < 2 || argc > 3)
    {
      result.valid = false;
      return result;
    }
    
    for (int i = 1; i < argc; ++i)
    {
      std::string arg(argv[i]);
      std::string value;

      if (vasyakin::splitArg(arg, "in:", value))
      {
        if (result.hasPersons)
        {
          result.valid = false;
          return result;
        }

        result.personsFile = value;
        result.hasPersons = true;
      }
      else if (vasyakin::splitArg(arg, "data:", value))
      {
        if (result.hasData)
        {
          result.valid = false;
          return result;
        }

        result.dataFile = value;
        result.hasData = true;
      }
      else
      {
        result.valid = false;
        return result;
      }
    }

    if (!result.hasData)
    {
      result.valid = false;
    }

    return result;
  }
}

int main(int argc, char** argv)
{
  if (argc > 3)
  {
    std::cerr << "Too mane arguments" << '\n';
    return 0;
  }

  Arguments args = parseArguments(argc, argv);
  
  if (!args.valid) {
    std::cerr << "invalid arguments\n";
    return 1;
  }
  
  vasyakin::Graph* root = nullptr;
  
  if (args.hasPersons)
  {
    std::ifstream personsStream(args.personsFile.c_str());
    if (!personsStream)
    {
      std::cerr << "cannot open persons file\n";
      vasyakin::clearGraph(root);
      return 2;
    }

    vasyakin::loadPersons(personsStream, root);
  }
  
  std::ifstream dataStream(args.dataFile.c_str());
  if (!dataStream)
  {
    std::cerr << "cannot open data file\n";
    vasyakin::clearGraph(root);
    return 2;
  }
  
  if (!vasyakin::loadMeetings(dataStream, root))
  {
    std::cerr << "invalid meetings data\n";
    vasyakin::clearGraph(root);
    return 3;
  }
  
  vasyakin::runCommands(std::cin, std::cout, root);
  
  vasyakin::clearGraph(root);
  
  return 0;
}
