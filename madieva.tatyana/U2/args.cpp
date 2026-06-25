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

  Config parseArgs(int argc, char * argv[]) {
    if (argc < 2 || argc > 3) {
      throw std::invalid_argument("invalid number of arguments");
    }

    Config config;
    bool hasPersons = false;
    bool hasMeets = false;

    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];

      if (startsWith(arg, "in:")) {
        if (hasPersons) {
          throw std::invalid_argument("duplicate persons file argument");
        }
        std::string filename = arg.substr(3);
        if (filename.empty()) {
          throw std::invalid_argument("empty persons filename");
        }
        config.persons_file_ = filename;
        hasPersons = true;
      } else if (startsWith(arg, "data:")) {
        if (hasMeets) {
          throw std::invalid_argument("duplicate meets file argument");
        }
        std::string filename = arg.substr(5);
        if (filename.empty()) {
          throw std::invalid_argument("empty meets filename");
        }
        config.meets_file_ = filename;
        hasMeets = true;
      } else {
        throw std::invalid_argument("unknown argument");
      }
    }

    if (!hasMeets) {
      throw std::invalid_argument("meets file is required");
    }

    return config;
  }

}