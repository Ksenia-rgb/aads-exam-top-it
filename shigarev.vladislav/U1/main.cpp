#include "parseargs.hpp"
#include "personio.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  shigarev::Args args = {"", "", false, false};
  if (!shigarev::parseArgs(argc, argv, args)) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  std::ifstream inputFile;
  if (args.hasInputFile) {
    inputFile.open(args.inputFile);
    if (!inputFile.is_open()) {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
  }
  std::istream& in = args.hasInputFile
      ? inputFile
      : std::cin;

  shigarev::ReadResult result = shigarev::readPersons(in);
  inputFile.close();

  std::ofstream outputFile;
  if (args.hasOutputFile) {
    outputFile.open(args.outputFile);
    if (!outputFile.is_open()) {
      std::cerr << "Cannot open output file\n";
      shigarev::destroyDynArray(result.persons);
      return 2;
    }
  }
  std::ostream& out = args.hasOutputFile
      ? outputFile
      : std::cout;

  shigarev::writePersons(out, result.persons);
  shigarev::writeStats(std::cerr, result.readCount,
      result.ignoredCount);
  shigarev::destroyDynArray(result.persons);
  return 0;
}
