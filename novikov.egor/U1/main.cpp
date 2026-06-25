#include <iostream>
#include "HashTable.hpp"
#include "List.hpp"
#include "Person.hpp"
#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
  if (argc > 3) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::string inFile;
  std::string outFile;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.substr(0, 3) == "in:") {
      inFile = arg.substr(3);
    } else if (arg.substr(0, 4) == "out:") {
      outFile = arg.substr(4);
    } else {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }
  std::ifstream inFileStream;
  std::istream *in = &std::cin;
  if (!inFile.empty()) {
    inFileStream.open(inFile);
    if (!inFileStream) {
      std::cerr << "Failed to open input file\n";
      return 2;
    }
    in = &inFileStream;
  }

  std::ofstream outFileStream;
  std::ostream *out = &std::cout;
  if (!outFile.empty()) {
    outFileStream.open(outFile);
    if (!outFileStream) {
      std::cerr << "Failed to open output file\n";
      return 2;
    }
    out = &outFileStream;
  }

  novikov::List< novikov::Person > persons;
  persons.head = nullptr;
  novikov::HashTable< bool, size_t > seen;
  seen.capacity = 101;
  seen.size = 0;
  seen.data = new novikov::HashNode< bool, size_t > *[seen.capacity];
  for (size_t i = 0; i < seen.capacity; ++i) {
    seen.data[i] = nullptr;
  }
  size_t id;
  std::string info;
  size_t succesCount = 0;
  size_t ignoredCount = 0;
  while (*in >> id && !(in->eof())) {
    *in >> info;
    if (info.empty()) {
      ignoredCount++;
      continue;
    }
    if (novikov::is_has(seen, id)) {
      ignoredCount++;
      continue;
    }
    novikov::insert(seen, id, true);
    novikov::push_back(persons, novikov::Person{id, info});
    succesCount++;
  }

  novikov::Node< novikov::Person > *cur = persons.head;
  while (cur) {
    *out << cur->val.id << " " << cur->val.info << "\n";
    cur = cur->next;
  }
  std::cerr << succesCount << " " << ignoredCount << "\n";
  clear(persons);
  clear(seen);
  return 0;
}
