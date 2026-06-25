#include "structures.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  using namespace karpenkov;
  if (argc > 3) {
    std::cerr << "Too mane args";
    return 0;
  }
  Args args = processArgs(argc, argv);
  if (!args.valid)
    return 1;
  std::istream *in = &std::cin;
  std::ifstream inputFile;
  if (!args.inputFile.empty()) {
    inputFile.open(args.inputFile);
    if (!inputFile.is_open())
      return 2;
    in = &inputFile;
  }
  HashTable *table = createHashTable(16);
  OrderArray *order = createOrderArray(16);
  size_t successCount = 0;
  size_t ignoredCount = 0;
  goodStringsCount(*in, table, order, successCount, ignoredCount);
  std::ostream *out = &std::cout;
  std::ofstream outputFile;
  if (!args.outputFile.empty()) {
    outputFile.open(args.outputFile);
    if (!outputFile.is_open())
      return 2;
    out = &outputFile;
  }
  writeData(*out, table, order);
  if (successCount != 0 || ignoredCount != 0) {
    std::cerr << successCount << " " << ignoredCount << std::endl;
  }
  destroyOrderArray(order);
  hashTableDestroy(table);
  return 0;
}
