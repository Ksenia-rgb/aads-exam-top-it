#include "processor.hpp"

int main(int argc, char* argv[]) {
  std::string inputFilename;
  std::string outputFilename;
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg.length() >= 3 && arg.substr(0, 3) == "in:") {
      if (!inputFilename.empty()) {
        std::cerr << "Error: Input file specified twice" << "\n";
        return 1;
      }
      inputFilename = arg.substr(3);
    } else if (arg.length() >= 4 && arg.substr(0, 4) == "out:") {
      if (!outputFilename.empty()) {
        std::cerr << "Error: Output file specified twice" << "\n";
        return 1;
      }
      outputFilename = arg.substr(4);
    } else {
      std::cerr << "Error: Invalid argument: " << arg << "\n";
      return 1;
    }
  }

  petrenko::DataProcessor processor;
  std::ifstream inputFile;
  if (!inputFilename.empty()) {
    inputFile.open(inputFilename);
    if (!inputFile.is_open()) {
      std::cerr << "Error: Cannot open input file: " << inputFilename << "\n";
      return 2;
    }
    processor.processInput(inputFile);
    inputFile.close();
  } else {
    processor.processInput(std::cin);
  }
  std::ofstream outputFile;
  std::ostream* outputStream = &std::cout;
  if (!outputFilename.empty()) {
    outputFile.open(outputFilename);
    if (!outputFile.is_open()) {
      std::cerr << "Error: Cannot open output file: " << outputFilename << "\n";
      return 2;
    }
    outputStream = &outputFile;
  }
  processor.outputResults(*outputStream);
  std::cerr << processor.getValidCount() << " " << processor.getIgnoredCount() << "\n";
  if (outputFile.is_open()) {
    outputFile.close();
  }
  return 0;
}
