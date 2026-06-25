#include <fstream>
#include <iostream>
#include <string>
#include <io.hpp>

int main(int argc, char** argv)
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Invalid arguments\n";
    return 0;
  }
  std::string inFile;
  std::string dataFile;
  bool hasIn = false;
  bool hasData = false;
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);
    if (arg.size() > 3 && arg.substr(0, 3) == "in:")
    {
      if (hasIn)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      inFile = arg.substr(3);
      hasIn = true;
    }
    else if (arg.size() > 5 && arg.substr(0, 5) == "data:")
    {
      if (hasData)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      dataFile = arg.substr(5);
      hasData = true;
    }
    else
    {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }
  if (!hasData)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  zharov::Array< zharov::Person > persons = zharov::makeArray< zharov::Person >(10);
  if (hasIn)
  {
    std::ifstream file_in(inFile);
    if (!file_in.is_open())
    {
      std::cerr << "Cannot open file\n";
      zharov::clear(persons);
      return 2;
    }
    size_t accepted = 0;
    size_t ignored = 0;
    zharov::readPersons(file_in, persons, accepted, ignored);
  }
  std::ifstream file_data(dataFile);
  if (!file_data.is_open())
  {
    std::cerr << "Cannot open file\n";
    zharov::clear(persons);
    return 2;
  }
  zharov::Array< zharov::Meet > meets = zharov::makeArray< zharov::Meet >(10);
  if (!zharov::readMeets(file_data, meets))
  {
    std::cerr << "Invalid data\n";
    zharov::clear(persons);
    zharov::clear(meets);
    return 3;
  }
  zharov::clear(persons);
  zharov::clear(meets);
}
