#include <fstream>
#include <iostream>

#include "arguments.hpp"

int main(int argc, char ** argv)
{
  samarin::options_t options{ false, "", false, "" };
  if (!samarin::parseArguments(argc, argv, options)) {
    std::cerr << "invalid arguments\n";
    return 1;
  }

  std::ifstream inputFile;
  if (options.hasInput) {
    inputFile.open(options.inputName);
    if (!inputFile.is_open()) {
      std::cerr << "cannot open input file\n";
      return 2;
    }
  }
  std::istream & input = options.hasInput ? inputFile : std::cin;
  static_cast< void >(input);

  return 0;
}
