#include <iostream>
#include <vector.hpp>
#include "input.hpp"
#include "person.hpp"

int main(int argc, char ** argv)
{
  using namespace chernov;

  std::string inFile, outFile;
  if (!parseArgs(argc, argv, inFile, outFile)) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  std::ifstream fin;
  if (!inFile.empty()) {
    fin.open(inFile);
    if (!fin.is_open()) {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
  }

  std::ofstream fout;
  if (!outFile.empty()) {
    fout.open(outFile);
    if (!fout.is_open()) {
      std::cerr << "Cannot open output file\n";
      return 2;
    }
  }

  std::istream & input = inFile.empty() ? std::cin : fin;
  std::ostream & output = outFile.empty() ? std::cout : fout;

  Vector< Person > persons;
  init(persons);
}
