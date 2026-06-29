#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include "cmds.hpp"

namespace
{
  bool startsWith(const std::string &str, const std::string &prefix)
  {
    if (str.size() < prefix.size()) {
      return false;
    }
    for (size_t i = 0; i < prefix.size(); ++i) {
      if (str[i] != prefix[i]) {
        return false;
      }
    }
    return true;
  }
}

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 3) {
    std::cerr << "Invalid arguments\n";
    return 0;
  }
  bool hasInputFile = false;
  bool hasDataFile = false;

  std::string inputFileName;
  std::string dataFileName;

  for (size_t i = 1; i < static_cast< size_t >(argc); ++i) {
    std::string argument = argv[i];

    if (startsWith(argument, "in:")) {
      if (hasInputFile) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasInputFile = true;
      inputFileName = argument.substr(3);
    } else if (startsWith(argument, "data:")) {
      if (hasDataFile) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasDataFile = true;
      dataFileName = argument.substr(5);
    } else {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }

  if (!hasDataFile) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  dirko::Vector< dirko::Person > persons;
  dirko::init(persons);

  if (hasInputFile) {
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
      std::cerr << "Cannot open file\n";
      dirko::clear(persons);
      return 2;
    }

    size_t ignored = 0;

    dirko::input(inputFile, persons, ignored);
  }

  dirko::Vector< dirko::Meet > meets;
  dirko::init(meets);

  try {
    std::ifstream dataFile(dataFileName);

    if (!dataFile.is_open()) {
      std::cerr << "Cannot open file\n";
      dirko::clear(persons);
      dirko::clear(meets);
      return 2;
    }

    dirko::readMeets(dataFile, meets);
    dirko::removeSelfMeets(meets);
    for (size_t i = 0; i < meets.size; ++i) {
      if (!dirko::containsPerson(persons, meets.data[i].first)) {
        dirko::Person anon;
        anon.id = meets.data[i].first;
        anon.info = "";
        dirko::add(persons, anon);
      }

      if (!dirko::containsPerson(persons, meets.data[i].second)) {
        dirko::Person anon;
        anon.id = meets.data[i].second;
        anon.info = "";
        dirko::add(persons, anon);
      }
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    dirko::clear(persons);
    dirko::clear(meets);
    return 3;
  }

  std::string command;

  while (std::cin >> command) {
    try {
      dirko::processCommand(std::cin, std::cout, persons, meets, command);
    } catch (const std::exception &) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  dirko::clear(persons);
  dirko::clear(meets);

  return 0;
}
