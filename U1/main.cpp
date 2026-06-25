#include <iostream>
#include "HashTable.hpp"
#include "List.hpp"
#include "Person.hpp"
#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
  if (argc > 3) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::string inFile;
  std::string outFile;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.substr(0, 3) == "in:") {
      inFile = arg.substr(3);
    } else if (arg.substr(0, 4) == "out:") {
      outFile = arg.substr(4);
    } else {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }
  std::ifstream inFileStream;
  std::istream *in = &std::cin;
  if (!inFile.empty()) {
    inFileStream.open(inFile);
    if (!inFileStream) {
      std::cerr << "Failed to open input file\n";
      return 2;
    }
    in = &inFileStream;
  }

  std::ofstream outFileStream;
  std::ostream *out = &std::cout;
  if (!outFile.empty()) {
    outFileStream.open(outFile);
    if (!outFileStream) {
      std::cerr << "Failed to open output file\n";
      return 2;
    }
    out = &outFileStream;
  }
}
