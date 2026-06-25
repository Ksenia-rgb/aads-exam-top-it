#include <exception>
#include <fstream>
#include <iostream>

#include "arguments.hpp"
#include "list.hpp"
#include "person.hpp"
#include "records.hpp"

namespace {
  const int exitInvalidArguments = 1;
  const int exitRuntimeError = 2;

  int writeResult(const samarin::Options & options,
      const samarin::detail::list_t< samarin::Person > & records)
  {
    std::ofstream outputFile;
    if (options.hasOutput) {
      outputFile.open(options.outputName);
      if (!outputFile.is_open()) {
        std::cerr << "cannot open output file\n";
        return exitRuntimeError;
      }
    }
    std::ostream & output = options.hasOutput ? outputFile : std::cout;
    samarin::writeRecords(output, records);
    if (!output) {
      std::cerr << "cannot write output\n";
      return exitRuntimeError;
    }
    return 0;
  }
}

int main(int argc, char ** argv)
{
  samarin::Options options{ false, "", false, "" };
  if (!samarin::parseArguments(argc, argv, options)) {
    std::cerr << "invalid arguments\n";
    return exitInvalidArguments;
  }

  std::ifstream inputFile;
  if (options.hasInput) {
    inputFile.open(options.inputName);
    if (!inputFile.is_open()) {
      std::cerr << "cannot open input file\n";
      return exitRuntimeError;
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
    std::cerr << counts.accepted << ' ' << counts.ignored << '\n';
    code = writeResult(options, records);
  } catch (const std::exception & error) {
    std::cerr << error.what() << '\n';
    code = exitRuntimeError;
  }
  samarin::detail::clear(records);
  return code;
}
