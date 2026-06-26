#include <iostream>
#include <person.hpp>
#include <vector.hpp>
#include "input.hpp"

int main(int argc, char ** argv)
{
  using namespace chernov;

  if (argc > 3) {
    std::cerr << "Too many arguments\n";
    return 0;
  }

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

  std::istream & input = inFile.empty() ? std::cin : fin;

  Vector< Person > persons;
  init(persons);

  size_t success = 0;
  size_t ignored = 0;
  std::string line;

  while (std::getline(input, line)) {
    size_t first = line.find_first_not_of(" \t");
    if (first == std::string::npos) {
      continue;
    }

    size_t space = line.find_first_of(" \t", first);
    if (space == std::string::npos) {
      ++ignored;
      continue;
    }

    std::string idStr = line.substr(first, space - first);
    size_t descStart = line.find_first_not_of(" \t", space);
    if (descStart == std::string::npos) {
      ++ignored;
      continue;
    }

    std::string description = line.substr(descStart);
    if (description.find_first_not_of(" \t") == std::string::npos) {
      ++ignored;
      continue;
    }

    size_t id;
    try {
      id = std::stoull(idStr);
    } catch (...) {
      ++ignored;
      continue;
    }

    if (findById(persons, id) != persons.size) {
      ++ignored;
      continue;
    }

    Person p{id, description};
    try {
      pushBack(persons, p);
    } catch (...) {
      destroy(persons);
      throw;
    }
    ++success;
  }

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
