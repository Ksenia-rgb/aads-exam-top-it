#include <fstream>
#include <iostream>
#include <string>
namespace
{
struct Options
{
  std::string dataFile;
  std::string personsFile;
  bool hasPersons;
};
bool parseArgs(int argc, char * argv[], Options & options)
{
  options.hasPersons = false;
  bool hasData = false;
  if (argc < 2 || argc > 3)
  {
    return false;
  }
  const std::string dataPrefix = "data:";
  const std::string inPrefix = "in:";
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg = argv[i];
    if (arg.compare(0, dataPrefix.size(), dataPrefix) == 0)
    {
      if (hasData)
      {
        return false;
      }
      const std::string name = arg.substr(dataPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.dataFile = name;
      hasData = true;
    }
    else if (arg.compare(0, inPrefix.size(), inPrefix) == 0)
    {
      if (options.hasPersons)
      {
        return false;
      }
      const std::string name = arg.substr(inPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.personsFile = name;
      options.hasPersons = true;
    }
    else
    {
      return false;
    }
  }
  return hasData;
}
}
int main(int argc, char * argv[])
{
  Options options{"", "", false};
  if (!parseArgs(argc, argv, options))
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::ifstream dataStream(options.dataFile);
  if (!dataStream.is_open())
  {
    std::cerr << "Cannot open data file\n";
    return 2;
  }
  if (options.hasPersons)
  {
    std::ifstream personsStream(options.personsFile);
    if (!personsStream.is_open())
    {
      std::cerr << "Cannot open persons file\n";
      return 2;
    }
  }
  return 0;
}
