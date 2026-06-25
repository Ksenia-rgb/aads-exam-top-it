#include "CommandLineOptions.h"

CommandLineOptions::CommandLineOptions()
  : inputFileName_(),
    dataFileName_(),
    hasInputFile_(false),
    hasDataFile_(false),
    valid_(false) {
}

bool CommandLineOptions::parse(int argc, char* argv[]) {
  if (argc < 2 || argc > 3) {
    valid_ = false;
    return false;
  }

  for (int i = 1; i < argc; ++i) {
    const char* arg = argv[i];
    if (arg[0] == 'i' && arg[1] == 'n' && arg[2] == ':') {
      if (hasInputFile_) {
        valid_ = false;
        return false;
      }
      inputFileName_ = arg + 3;
      if (inputFileName_.empty()) {
        valid_ = false;
        return false;
      }
      hasInputFile_ = true;
    } else if (arg[0] == 'd' && arg[1] == 'a' && arg[2] == 't' && arg[3] == 'a' && arg[4] == ':') {
      if (hasDataFile_) {
        valid_ = false;
        return false;
      }
      dataFileName_ = arg + 5;
      if (dataFileName_.empty()) {
        valid_ = false;
        return false;
      }
      hasDataFile_ = true;
    } else {
      valid_ = false;
      return false;
    }
  }

  if (!hasDataFile_) {
    valid_ = false;
    return false;
  }
  valid_ = true;
  return true;
}

bool CommandLineOptions::isValid() const {
  return valid_;
}

bool CommandLineOptions::hasInputFile() const {
  return hasInputFile_;
}

bool CommandLineOptions::hasDataFile() const {
  return hasDataFile_;
}

const std::string& CommandLineOptions::inputFileName() const {
  return inputFileName_;
}

const std::string& CommandLineOptions::dataFileName() const {
  return dataFileName_;
}
