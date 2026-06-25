#include <exception>
#include <fstream>
#include <iostream>

#include "arguments.hpp"
#include "list.hpp"
#include "person.hpp"
#include "records.hpp"

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

  samarin::detail::list_t< samarin::Person > records{ nullptr, nullptr };
  int code = 0;
  try {
    const samarin::counts_t counts = samarin::readRecords(input, records);
    if (options.hasInput) {
      inputFile.close();
    }
    std::ofstream outputFile;
    if (options.hasOutput) {
      outputFile.open(options.outputName);
    }
    if (options.hasOutput && !outputFile.is_open()) {
      std::cerr << "cannot open output file\n";
      code = 2;
    } else {
      std::ostream & output = options.hasOutput ? outputFile : std::cout;
      samarin::writeRecords(output, records);
      std::cerr << counts.accepted << ' ' << counts.ignored << '\n';
      if (!output) {
        std::cerr << "cannot write output\n";
        code = 2;
      }
    }
  } catch (const std::exception & error) {
    std::cerr << error.what() << '\n';
    code = 2;
  }
  samarin::detail::clear(records);
  return code;
}
