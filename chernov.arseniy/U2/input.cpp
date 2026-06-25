#include "input.hpp"
#include <fstream>
#include <iostream>
#include <utils.hpp>

bool chernov::parseArgs(int argc, char ** argv, std::string & inFile, std::string & dataFile)
{
  if (argc < 2 || argc > 3) {
    return false;
  }

  bool hasData = false;
  bool hasIn = false;
  inFile.clear();
  dataFile.clear();

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.rfind("in:", 0) == 0) {
      if (hasIn) {
        return false;
      }
      inFile = arg.substr(3);
      hasIn = true;
    } else if (arg.rfind("data:", 0) == 0) {
      if (hasData) {
        return false;
      }
      dataFile = arg.substr(5);
      hasData = true;
    } else {
      return false;
    }
  }

  return hasData;
}

int chernov::readMeetings(const std::string & filename, Vector< Meeting > & meetings, Vector< size_t > & allIds)
{
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Cannot open data file\n";
    return 2;
  }

  std::string line;
  while (std::getline(fin, line)) {
    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos) {
      continue;
    }

    size_t id1 = 0, id2 = 0, duration = 0;
    size_t pos = start;
    size_t count = 0;
    bool ok = true;

    for (int i = 0; i < 3; ++i) {
      size_t space = line.find_first_of(" \t", pos);
      if (space == std::string::npos && i < 2) {
        ok = false;
        break;
      }
      std::string token = (space == std::string::npos) ? line.substr(pos) : line.substr(pos, space - pos);
      if (token.empty()) {
        ok = false;
        break;
      }
      try {
        size_t val = std::stoull(token);
        if (i == 0) {
          id1 = val;
        } else if (i == 1) {
          id2 = val;
        } else if (i == 2) {
          duration = val;
        }
      } catch (...) {
        ok = false;
        break;
      }
      pos = (space == std::string::npos) ? std::string::npos : space + 1;
      ++count;
    }

    if (!ok || count != 3) {
      std::cerr << "Invalid meeting data\n";
      return 3;
    }

    size_t after = line.find_first_not_of(" \t", pos);
    if (after != std::string::npos) {
      std::cerr << "Invalid meeting data\n";
      return 3;
    }

    Date date{0, 0, 0};
    addMeeting(meetings, id1, id2, duration, date);
    addUniqueId(allIds, id1);
    addUniqueId(allIds, id2);
  }
  return 0;
}

int chernov::readPersonsFromFile(const std::string & filename, Vector< Person > & persons)
{
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  std::string line;
  while (std::getline(fin, line)) {
    size_t first = line.find_first_not_of(" \t");
    if (first == std::string::npos) {
      continue;
    }

    size_t space = line.find_first_of(" \t", first);
    if (space == std::string::npos) {
      continue;
    }

    std::string idStr = line.substr(first, space - first);
    size_t descStart = line.find_first_not_of(" \t", space);
    if (descStart == std::string::npos) {
      continue;
    }

    std::string description = line.substr(descStart);
    if (description.find_first_not_of(" \t") == std::string::npos) {
      continue;
    }

    size_t id;
    try {
      id = std::stoull(idStr);
    } catch (...) {
      continue;
    }

    if (findById(persons, id) != persons.size) {
      continue;
    }

    Person p{id, description};
    pushBack(persons, p);
  }

  return 0;
}

void chernov::parseCommandLine(const std::string & line, Vector< std::string > & tokens)
{
  init(tokens);

  size_t pos = 0;
  while (pos < line.size()) {
    size_t start = line.find_first_not_of(" \t", pos);
    if (start == std::string::npos) {
      break;
    }

    std::string token;
    if (line[start] == '"') {
      size_t end = line.find('"', start + 1);
      if (end == std::string::npos) {
        destroy(tokens);
        return;
      }
      token = line.substr(start + 1, end - start - 1);
      pos = end + 1;
    } else {
      size_t end = line.find_first_of(" \t", start);
      if (end == std::string::npos) {
        token = line.substr(start);
        pos = line.size();
      } else {
        token = line.substr(start, end - start);
        pos = end + 1;
      }
    }

    try {
      pushBack(tokens, token);
    } catch (...) {
      destroy(tokens);
      throw;
    }
  }
}
