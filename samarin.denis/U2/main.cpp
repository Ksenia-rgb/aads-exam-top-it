#include <exception>
#include <fstream>
#include <iostream>

#include "arguments.hpp"
#include "commands.hpp"
#include "io.hpp"
#include "model.hpp"

namespace {
  const int exitInvalidArguments = 1;
  const int exitOpenError = 2;
  const int exitDataError = 3;

  int run(const samarin::Options & options, samarin::Dataset & data)
  {
    if (options.hasPersons) {
      std::ifstream personsFile(options.personsName);
      if (!personsFile.is_open()) {
        std::cerr << "cannot open persons file\n";
        return exitOpenError;
      }
      samarin::readPersons(personsFile, data);
    }
    std::ifstream dataFile(options.dataName);
    if (!dataFile.is_open()) {
      std::cerr << "cannot open data file\n";
      return exitOpenError;
    }
    if (!samarin::readMeetings(dataFile, data)) {
      std::cerr << "invalid meetings data\n";
      return exitDataError;
    }
    samarin::runCommands(std::cin, std::cout, data);
    return 0;
  }
}

int main(int argc, char ** argv)
{
  samarin::Options options{ false, "", "" };
  if (!samarin::parseArguments(argc, argv, options)) {
    std::cerr << "invalid arguments\n";
    return exitInvalidArguments;
  }

  samarin::Dataset data{ { nullptr, nullptr }, { nullptr, nullptr } };
  int code = 0;
  try {
    code = run(options, data);
  } catch (const std::exception & error) {
    std::cerr << error.what() << '\n';
    code = exitOpenError;
  }
  samarin::clearDataset(data);
  return code;
}
