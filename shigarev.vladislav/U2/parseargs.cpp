#include "parseargs.hpp"

#include <string>

namespace {
  const size_t IN_PREFIX_LEN = 3;
  const size_t DATA_PREFIX_LEN = 5;

  bool startsWith(const std::string& str,
      const char* prefix, size_t len)
  {
    if (str.size() < len) {
      return false;
    }
    return str.compare(0, len, prefix) == 0;
  }
}

bool shigarev::parseArgs(int argc, const char* const* argv,
    Args& args)
{
  args = {"", "", false, false};

  if (argc < 2 || argc > 3) {
    return false;
  }

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (startsWith(arg, "in:", IN_PREFIX_LEN)) {
      if (args.hasInputFile) {
        return false;
      }
      args.inputFile = arg.substr(IN_PREFIX_LEN);
      args.hasInputFile = true;
    } else if (startsWith(arg, "data:", DATA_PREFIX_LEN)) {
      if (args.hasDataFile) {
        return false;
      }
      args.dataFile = arg.substr(DATA_PREFIX_LEN);
      args.hasDataFile = true;
    } else {
      return false;
    }
  }

  if (!args.hasDataFile) {
    return false;
  }

  return true;
}
