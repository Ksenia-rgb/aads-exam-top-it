#include <iostream>
#include <utils.hpp>
#include "commands.hpp"
#include "input.hpp"

int main(int argc, char * argv[])
{
  using namespace chernov;

  std::string inFile, dataFile;
  if (!parseArgs(argc, argv, inFile, dataFile)) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  Vector< Person > persons;
  init(persons);

  if (!inFile.empty()) {
    int ret = readPersonsFromFile(inFile, persons);
    if (ret != 0) {
      destroy(persons);
      return ret;
    }
  }

  Vector< Meeting > meetings;
  init(meetings);
  Vector< size_t > allIds;
  init(allIds);

  try {
    if (!dataFile.empty()) {
      int ret = readMeetings(dataFile, meetings, allIds);
      if (ret != 0) {
        destroy(allIds);
        destroy(meetings);
        destroy(persons);
        return ret;
      }
    }

    for (size_t i = 0; i < persons.size; ++i) {
      addUniqueId(allIds, persons.data[i].id);
    }

    std::string line;
    while (std::getline(std::cin, line)) {
      Vector< std::string > tokens;
      parseCommandLine(line, tokens);

      if (tokens.size == 0) {
        destroy(tokens);
        continue;
      }

      std::string cmd = tokens.data[0];

      if (cmd == "anons") {
        if (tokens.size != 1) {
          std::cout << "<INVALID COMMAND>\n";
        } else {
          printAnons(allIds, persons);
        }
      } else if (cmd == "desc") {
        if (tokens.size != 2) {
          std::cout << "<INVALID COMMAND>\n";
        } else {
          size_t id;
          try {
            id = std::stoull(tokens.data[1]);
          } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            destroy(tokens);
            continue;
          }
          size_t idx = findById(persons, id);
          if (idx == persons.size) {
            std::cout << "<ANON>\n";
          } else {
            std::cout << persons.data[idx].info << '\n';
          }
        }
      } else {
        std::cout << "<INVALID COMMAND>\n";
      }

      destroy(tokens);
    }
  } catch (...) {
    destroy(allIds);
    destroy(meetings);
    destroy(persons);
  }
}
