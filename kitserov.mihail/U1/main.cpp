#include <iostream>
#include <fstream>
#include <person.hpp>
#include <utils.hpp>
int main(int argc, char* argv[])
{
  using namespace kitserov;
  std::ifstream inFile;
  std::ifstream outFile;
  std::istream* inputStream = &std::cin;
  std::ostream* outputStream = &std::cout;
  if (argc > 3) {
    std::cerr << "Too many arcs\n";
    return 1;
  }
  bool inSet = false;
  bool outSet = false;
  for (size_t i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.compare(0, 3, "in:") == 0) {
      if (inSet) {
        std::cerr << "Two input files\n";
        return 1;
      } else {
        inFile.open(arg.substr(3));
        if (!inFile.is_open()) {
          std::cerr << "Failed to open file: " << arg.substr(3) << "\n";
          return 1;
        }
        inputStream = &inFile;
        inSet = true;
      }
    } else if (arg.compare(0, 4, "out:") == 0) {
      if (outSet) {
        std::cerr << "Two output files\n";
        return 1;
      } else {
        outFile.open(arg.substr(4));
        if (!outFile.is_open()) {
          std::cerr << "Failed to open file: " << arg.substr(4) << "\n";
          return 1;
        }
        outputStream = &outFile;
        outSet = true;
      }
    }
  }
}