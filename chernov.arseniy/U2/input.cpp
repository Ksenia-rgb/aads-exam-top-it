#include "input.hpp"

bool chernov::parseArgs(int argc, char ** argv, std::string & inFile, std::string & dataFile)
{
  if (argc < 2 || argc > 3) {
    return false;
  }

  bool hasData = false;
  bool hasIn = false;
  inFile.clear();
  dataFile.clear();

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.rfind("in:", 0) == 0) {
      if (hasIn) {
        return false;
      }
      inFile = arg.substr(3);
      hasIn = true;
    } else if (arg.rfind("data:", 0) == 0) {
      if (hasData) {
        return false;
      }
      dataFile = arg.substr(5);
      hasData = true;
    } else {
      return false;
    }
  }

  return hasData;
}
