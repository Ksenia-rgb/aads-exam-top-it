#include "args.hpp"
#include <stdexcept>
#include <cstring>

namespace madieva {

namespace {

  bool startsWith(const std::string& str, const char* prefix) {
    std::size_t prefixLen = std::strlen(prefix);
    if (str.size() < prefixLen) {
      return false;
    }
    return str.compare(0, prefixLen, prefix) == 0;
  }

}

Config parseArgs(int argc, char* argv[]) {
  if (argc > 3) {
    throw std::invalid_argument("too many arguments");
  }

  Config config;
  bool hasInput = false;
  bool hasOutput = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (startsWith(arg, "in:")) {
      if (hasInput) {
        throw std::invalid_argument("duplicate input argument");
      }
      std::string filename = arg.substr(3);
      if (filename.empty()) {
        throw std::invalid_argument("empty input filename");
      }
      config.input_file_ = filename;
      hasInput = true;
    } else if (startsWith(arg, "out:")) {
      if (hasOutput) {
        throw std::invalid_argument("duplicate output argument");
      }
      std::string filename = arg.substr(4);
      if (filename.empty()) {
        throw std::invalid_argument("empty output filename");
      }
      config.output_file_ = filename;
      hasOutput = true;
    } else {
      throw std::invalid_argument("unknown argument");
    }
  }

  return config;
}

}