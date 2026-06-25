#include <iostream>
#include "HashTable.hpp"
#include "List.hpp"
#include "Person.hpp"
#include <string>

int main(int argc, char* argv[])
{
  if(argc > 3)
  {
    std::cerr<<"Invalid arguments";
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
}
