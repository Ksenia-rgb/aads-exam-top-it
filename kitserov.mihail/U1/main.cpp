#include <iostream>
#include <fstream>
#include <person.hpp>
#include <utils.hpp>
int main(int argc, char* argv[])
{
  using namespace kitserov;
  std::ifstream inFile;
  std::ofstream outFile;
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
      if (!chooseStream< std::istream, std::ifstream >(inputStream, inFile, inSet, arg, 3)) {
        std::cerr << "Error in openning argument" << arg.substr(3) << "\n";
        return 1;
      }
    } else if (arg.compare(0, 4, "out:") == 0) {
      if (!chooseStream< std::ostream, std::ofstream >(outputStream, outFile, outSet, arg, 4)) {
        std::cerr << "Error in openning argument" << arg.substr(4) << "\n";
        return 1;
      }
    } else {
      std::cerr << "Unknown arg\n";
      return 1;
    }
  }
}