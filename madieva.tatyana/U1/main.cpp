#include "args.hpp"
#include "parser.hpp"
#include "vector.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

int main(int argc, char * argv[])
{
  try {
    madieva::Config config = madieva::parseArgs(argc, argv);

    std::istream * inStream = &std::cin;
    std::ifstream inFile;
    if (!config.input_file_.empty()) {
      inFile.open(config.input_file_);
      if (!inFile) {
        return 2;
      }
      inStream = &inFile;
    }
    madieva::PersonArray persons = madieva::createArray();
    std::size_t successCount = 0;
    std::size_t ignoredCount = 0;
    std::string line;
    while (std::getline(*inStream, line)) {
      bool allSpaces = true;
      for (std::size_t i = 0; i < line.size(); ++i) {
        if (!std::isspace(static_cast< unsigned char >(line[i]))) {
          allSpaces = false;
          break;
        }
      }
      if (allSpaces) {
        continue;
      }
      madieva::Person person;
      if (!madieva::parseLine(line, person)) {
        ++ignoredCount;
        continue;
      }

      bool duplicate = false;
      for (std::size_t i = 0; i < madieva::getSize(persons); ++i) {
        if (madieva::at(persons, i).id_ == person.id_) {
          duplicate = true;
          break;
        }
      }
      if (duplicate) {
        ++ignoredCount;
        continue;
      }

      madieva::pushBack(persons, person);
      ++successCount;
    }

    if (inFile.is_open()) {
      inFile.close();
    }

    std::ostream * outStream = &std::cout;
    std::ofstream outFile;
    if (!config.output_file_.empty()) {
      outFile.open(config.output_file_);
      if (!outFile) {
        std::cerr << "cannot open output file" << "\n";
        madieva::destroyArray(persons);
        return 2;
      }
      outStream = &outFile;
    }

    for (std::size_t i = 0; i < madieva::getSize(persons); ++i) {
      const madieva::Person& p = madieva::at(persons, i);
      *outStream << p.id_ << " " << p.info_ << "\n";
    }

    if (successCount == 0 && ignoredCount == 0) {
      std::cerr << "\n";
      return 0;
    }

    std::cerr << successCount << " " << ignoredCount << "\n";

    madieva::destroyArray(persons);
    return 0;
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << "\n";
    return 2;
  } catch (const std::bad_alloc&) {
    std::cerr << "out of memory" << "\n";
    return 0;
  }
}
