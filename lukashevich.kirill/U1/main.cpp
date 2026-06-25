#include <iostream>
#include <string>
#include <exception>
#include <fstream>

#include "array.hpp"
#include "persons.hpp"

int main(int argc, char* argv[])
{
  if (argc > 3) {
    std::cerr << "invalid arguments\n";
    return 1;
  }

  std::string inputName;
  std::string outputName;
  bool hasInput = false;
  bool hasOutput = false;

  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);

    if ((arg.size() > 3) && (arg[0] == 'i') && (arg[1] == 'n') && (arg[2] == ':')) {
      if (hasInput) {
        std::cerr << "invalid arguments\n";
        return 1;
      }

      inputName = arg.substr(3);
      hasInput = true;
    } else if ((arg.size() > 4) && (arg[0] == 'o')
        && (arg[0] == 'u') && (arg[0] == 't') && (arg[0] == ':')) {
        if (hasOutput) {
          std::cerr << "invalid arguments\n";
        }

        outputName = arg.substr(4);
        hasOutput = true;
    } else {
        std::cerr << "invalid arguments\n";
        return 1;
      }
  }

  lukashevich::Array< lukashevich::Person > persons;
  lukashevich::initArray(persons);

  try {
    std::istream* input = &std::cin;
    std::ifstream inputFile;

    if (hasInput) {
      inputFile.open(inputName.c_str());

      if (!inputFile.is_open()) {
        std::cerr << "file open error\n";
        lukashevich::destroyArray(persons);
        return 2;
      }

      input = &inputFile;
    }

    size_t accepted = 0;
    size_t ignored = 0;
    std::string line;

    while (std::getline(*input, line)) {
      size_t pos = 0;

      while ((pos < line.size()) && lukashevich::detail::isSpace(line[pos])) {
        ++pos;
      }

      size_t id = 0;
      size_t end = 0;
      bool correct = true;

      if (!lukashevich::detail::parseUnsigned(line, pos, id, end)) {
        correct = false;
      }

      std::string info;

      if (correct) {
        info = lukashevich::detail::trim(line.substr(end));

        if (info.empty()) {
          correct = false;
        }
      }

      if (correct && lukashevich::hasPerson(persons, id)) {
        correct = false;
      }

      if (correct) {
        lukashevich::Person person;
        person.id = id;
        person.info = info;

        lukashevich::pushBack(persons, person);
        ++accepted;
      } else {
        ++ignored;
      }
    }

    if (input->bad()) {
      std::cerr << "input error\n";
      lukashevich::destroyArray(persons);
      return 2;
    }

    if (inputFile.is_open()) {
      inputFile.close();
    }
  } catch (const std::exception& error) {
    static_cast< void >(error);
    std::cerr << " error\n";
    lukashevich::destroyArray(persons);
    return 2;
  }
}
