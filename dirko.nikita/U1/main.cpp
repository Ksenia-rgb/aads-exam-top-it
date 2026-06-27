#include <cstddef>
#include <string>
#include <fstream>
#include <iostream>
#include <person.hpp>
#include <vector.hpp>

int main(int argc, char *argv[])
{
  if (argc > 3) {
    std::cerr << "Invalid arguments\n";
    return 0;
  }

  std::string inFilename = "";
  std::string outFilename = "";
  bool inSet = false;
  bool outSet = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg.find("in:") == 0) {
      if (inSet) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      inFilename = arg.substr(3);
      if (inFilename.empty()) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      inSet = true;
    } else if (arg.find("out:") == 0) {
      if (outSet) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      outFilename = arg.substr(4);
      if (outFilename.empty()) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      outSet = true;
    } else {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }
  dirko::Vector< dirko::Person > persons{nullptr, 0, 0};
  size_t ignored = 0;
  if (inSet) {
    std::ifstream fin(inFilename);
    if (!fin.is_open()) {
      return 2;
    }
    dirko::input(fin, persons, ignored);
  } else {
    dirko::input(std::cin, persons, ignored);
  }

  std::cerr << persons.size << ' ' << ignored << '\n';
  if (outSet) {
    std::ofstream fout(outFilename);
    if (!fout.is_open()) {
      dirko::clear(persons);
      return 2;
    }
    dirko::output(fout, persons);
  } else {
    dirko::output(std::cout, persons);
  }
  dirko::clear(persons);
}
