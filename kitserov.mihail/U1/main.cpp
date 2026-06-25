#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include "person.hpp"
#include "utils1.hpp"
int main(int argc, char* argv[])
{
  using namespace kitserov;
  std::ifstream inFile;
  std::ofstream outFile;
  std::istream* inputStream = &std::cin;
  std::ostream* outputStream = &std::cout;
  if (argc > 3) {
    std::cerr << "Too many arcs\n";
    return 0;
  }
  bool inSet = false;
  bool outSet = false;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.compare(0, 3, "in:") == 0) {
      std::pair< bool, int > pair = chooseStream< std::istream, std::ifstream >(inputStream, inFile, inSet, arg, 3);
      if (!(pair.first)) {
        std::cerr << "Error in openning argument" << arg.substr(3) << "\n";
        return pair.second;
      }
    } else if (arg.compare(0, 4, "out:") == 0) {
      std::pair< bool, int > pair = chooseStream< std::ostream, std::ofstream >(outputStream, outFile, outSet, arg, 4);
      if (!(pair.first)) {
        std::cerr << "Error in openning argument" << arg.substr(4) << "\n";
        return pair.second;
      }
    } else {
      std::cerr << "Unknown arg\n";
      return 1;
    }
  }
  PersonsContainer storage{nullptr, 0, 0};

  std::string line;
  size_t succs = 0;
  size_t ignored = 0;
  try {
    while (std::getline(*inputStream, line)) {
      size_t id = 0;
      std::string info;
      if (readLine(line, id, info)) {
        if (addPerson(storage, id, info)) {
          ++succs;
        } else {
          ++ignored;
        }
      } else {
        ++ignored;
      }
    }
  } catch (const std::bad_alloc&) {
    std::cerr << "Bad alloc memory\n";
    destroy(storage);
    return 2;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    destroy(storage);
    return 2;
  }
  printAll(storage, *outputStream);
  std::cerr << succs << " " << ignored << "\n";
  destroy(storage);
  return 0;
}
