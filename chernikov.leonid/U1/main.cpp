#include <iostream>
#include <fstream>
#include "file_utils.hpp"
#include "input_parser.hpp"
#include "hash_table.hpp"

int main(int argc, char *argv[])
{
  chernikov::FileConfig config;
  if (!chernikov::parseArguments(argc, argv, config, std::cerr))
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  std::ifstream inputFileStream;
  std::ofstream outputFileStream;
  std::istream *input = nullptr;
  std::ostream *output = nullptr;

  if (!chernikov::openFiles(config, inputFileStream, outputFileStream, input, output))
  {
    std::cerr << "Failed to open files\n";
    return 2;
  }

  chernikov::ParseResult result = chernikov::parseInput(*input, *output);

  std::cerr << result.validCount << " " << result.ignoredCount << "\n";

  chernikov::closeFiles(inputFileStream, outputFileStream);

  return 0;
}
