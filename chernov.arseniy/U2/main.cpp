#include <iostream>
#include <input.hpp>
#include <utils.hpp>
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace chernov;

  if (argc > 3) {
    std::cerr << "Too many arguments\n";
    return 0;
  }

  Vector< Person > persons;
  Vector< Meeting > meetings;
  Vector< size_t > allIds;

  init(persons);
  init(meetings);
  init(allIds);

  try {
    std::string inFile, dataFile;
    if (!parseArgsU2(argc, argv, inFile, dataFile)) {
      std::cerr << "Invalid arguments\n";
      destroy(persons);
      destroy(meetings);
      destroy(allIds);
      return 1;
    }

    if (!inFile.empty()) {
      size_t ignored = 0;
      int ret = readPersonsFromFile(inFile, persons, ignored);
      if (ret != 0) {
        destroy(persons);
        destroy(meetings);
        destroy(allIds);
        return ret;
      }
    }

    int ret = readMeetingsFromFile(dataFile, meetings, allIds);
    if (ret != 0) {
      destroy(persons);
      destroy(meetings);
      destroy(allIds);
      return ret;
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
      bool valid = true;
      size_t id = 0, id2 = 0, duration = 0;

      if (cmd == "anons") {
        valid = (tokens.size == 1);
        if (valid) {
          printAnons(allIds, persons);
        }
      } else if (cmd == "desc") {
        valid = (tokens.size == 2 && parseSize(tokens.data[1], id) && hasIdInAll(allIds, id));
        if (valid) {
          size_t idx = findById(persons, id);
          if (idx == persons.size) {
            std::cout << "<ANON>\n";
          } else {
            std::cout << persons.data[idx].info << '\n';
          }
        }
      } else if (cmd == "redesc") {
        valid =
          (tokens.size == 3 && parseSize(tokens.data[1], id) && processRedesc(persons, allIds, id, tokens.data[2]));
      } else if (cmd == "deanon") {
        valid = (tokens.size == 3 && parseSize(tokens.data[1], id) && parseSize(tokens.data[2], id2) &&
          processDeanon(persons, meetings, allIds, id, id2));
      } else if (cmd == "meets" || cmd == "meet") {
        valid = (tokens.size == 2 && parseSize(tokens.data[1], id) && hasIdInAll(allIds, id));
        if (valid)
          printMeets(meetings, id);
      } else if (cmd == "commons") {
        valid = (tokens.size == 3 && parseSize(tokens.data[1], id) && parseSize(tokens.data[2], id2) &&
          hasIdInAll(allIds, id) && hasIdInAll(allIds, id2));
        if (valid)
          printCommons(meetings, id, id2);
      } else if (cmd == "less" || cmd == "greater") {
        valid = (tokens.size == 3 && parseSize(tokens.data[1], duration) && parseSize(tokens.data[2], id) &&
          hasIdInAll(allIds, id));
        if (valid)
          printDurationFiltered(meetings, id, duration, cmd == "greater");
      } else if (cmd == "out-persons") {
        valid = (tokens.size == 2 && writePersons(tokens.data[1], persons));
      } else {
        valid = false;
      }

      if (!valid) {
        std::cout << "<INVALID COMMAND>\n";
      }
      destroy(tokens);
    }

    destroy(persons);
    destroy(meetings);
    destroy(allIds);
  } catch (...) {
    destroy(persons);
    destroy(meetings);
    destroy(allIds);
    return 1;
  }
}
