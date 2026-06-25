#include <iostream>
#include <string>
#include <exception>
#include <fstream>

#include "array.hpp"
#include "persons.hpp"

int main(int argc, char* argv[])
{
  if (argc > 3) {
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
        && (arg[1] == 'u') && (arg[2] == 't') && (arg[3] == ':')) {
        if (hasOutput) {
          std::cerr << "invalid arguments\n";
          return 1;
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
      if (lukashevich::detail::trim(line).empty()) {
        continue;
      }

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

    std::ostream* output = &std::cout;
    std::ofstream outputFile;

    if (hasOutput) {
      outputFile.open(outputName.c_str());

      if (!outputFile.is_open()) {
        std::cerr << "file open error\n";
        lukashevich::destroyArray(persons);
        return 2;
      }

      output = &outputFile;
    }

    for (size_t i = 0; i < persons.size_; ++i) {
      *output << persons.data_[i].id << ' ' << persons.data_[i].info << '\n';
    }

    if (!(*output)) {
      std::cerr << "ouput error\n";
      lukashevich::destroyArray(persons);
      return 2;
    }

    if ((accepted != 0) || (ignored != 0)) {
      std::cerr << accepted << ' ' << ignored << '\n';
    }
    lukashevich::destroyArray(persons);
    return 0;

  } catch (const std::exception& error) {
    static_cast< void >(error);
    std::cerr << " error\n";
    lukashevich::destroyArray(persons);
    return 2;
  }
}
