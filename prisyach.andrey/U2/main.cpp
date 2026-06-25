#include "CommandLineOptions.h"
#include "CommandProcessor.h"
#include "DataStore.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  CommandLineOptions options;
  if (!options.parse(argc, argv)) {
    std::fprintf(stderr, "Invalid command line arguments\n");
    return 1;
  }

  std::FILE* personsFile = nullptr;
  if (options.hasInputFile()) {
    personsFile = std::fopen(options.inputFileName().c_str(), "r");
    if (personsFile == nullptr) {
      std::fprintf(stderr, "Cannot open input file\n");
      return 2;
    }
  }

  std::FILE* meetingsFile = std::fopen(options.dataFileName().c_str(), "r");
  if (meetingsFile == nullptr) {
    if (personsFile != nullptr) {
      std::fclose(personsFile);
    }
    std::fprintf(stderr, "Cannot open data file\n");
    return 2;
  }

  DataStore dataStore;
  std::string error;
  if (personsFile != nullptr) {
    if (!dataStore.loadPersons(personsFile, error)) {
      std::fclose(personsFile);
      std::fclose(meetingsFile);
      std::fprintf(stderr, "%s\n", error.c_str());
      return 3;
    }
    std::fclose(personsFile);
  }

  if (!dataStore.loadMeetings(meetingsFile, error)) {
    std::fclose(meetingsFile);
    std::fprintf(stderr, "%s\n", error.c_str());
    return 3;
  }
  std::fclose(meetingsFile);

  CommandProcessor processor(dataStore);
  std::string line;
  while (true) {
    if (!std::getline(std::cin, line)) {
      break;
    }
    processor.processCommandLine(line);
  }
  return 0;
}
