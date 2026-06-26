#include <iostream>
#include <input.hpp>
#include <person.hpp>
#include <vector.hpp>

int main(int argc, char ** argv)
{
  using namespace chernov;

  if (argc > 3) {
    std::cerr << "Too many arguments\n";
    return 0;
  }

  std::string inFile, outFile;
  if (!parseArgsU1(argc, argv, inFile, outFile)) {
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

  std::istream & input = inFile.empty() ? std::cin : fin;

  Vector< Person > persons;
  init(persons);

  size_t ignored = 0;
  int ret = readPersonsFromStream(input, persons, ignored);
  if (ret != 0) {
    destroy(persons);
    return ret;
  }
  size_t success = persons.size;

  if (!inFile.empty()) {
    fin.close();
  }

  std::ofstream fout;
  if (!outFile.empty()) {
    fout.open(outFile);
    if (!fout.is_open()) {
      std::cerr << "Cannot open output file\n";
      destroy(persons);
      return 2;
    }
  }

  std::ostream & output = outFile.empty() ? std::cout : fout;

  if (persons.size) {
    output << persons.data[0].id << ' ' << persons.data[0].info;
  }
  for (size_t i = 1; i < persons.size; ++i) {
    output << '\n' << persons.data[i].id << ' ' << persons.data[i].info;
  }
  output << '\n';

  std::cerr << success << ' ' << ignored << '\n';

  destroy(persons);
}
