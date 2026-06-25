#include "processor.hpp"

int main(int argc, char* argv[]) {
  std::string inputFilename;
  std::string outputFilename;
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg.rfind("in:", 0) == 0) {
      if (!inputFilename.empty()) {
        std::cerr << "Error: Input file specified twice" << "\n";
        return 1;
      }
      inputFilename = arg.substr(3);
    } else if (arg.rfind("out:", 0) == 0) {
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
  if (argc > 3) {
    std::cerr << "Error: Too many arguments" << "\n";
    return 1;
  }
  return 0;
}
