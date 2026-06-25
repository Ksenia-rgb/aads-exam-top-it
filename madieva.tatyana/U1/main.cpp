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

    std::ostream* outStream = &std::cout;
    std::ofstream outFile;
    if (!config.output_file_.empty()) {
      outFile.open(config.output_file_);
      if (!outFile) {
        std::cerr << "cannot open output file" << std::endl;
        madieva::destroyArray(persons);
        return 2;
      }
      outStream = &outFile;
    }

    for (std::size_t i = 0; i < madieva::getSize(persons); ++i) {
      const madieva::Person& p = madieva::at(persons, i);
      *outStream << p.id_ << " " << p.info_ << "\n";
    }

    std::cerr << successCount << " " << ignoredCount << std::endl;

    madieva::destroyArray(persons);
    return 0;
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (const std::bad_alloc&) {
    std::cerr << "out of memory" << std::endl;
    return 2;
  }
}
