#include <input.hpp>

bool parseArgs(int argc, char * argv[], std::string & inFile, std::string & outFile)
{
  if (argc > 3) {
    return false;
  }

  bool hasIn = false;
  bool hasOut = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg.rfind("in:", 0) == 0) {
      if (hasIn) {
        return false;
      }
      inFile = arg.substr(3);
      hasIn = true;
    } else if (arg.rfind("out:", 0) == 0) {
      if (hasOut) {
        return false;
      }
      outFile = arg.substr(4);
      hasOut = true;
    } else {
      return false;
    }
  }

  return true;
}
