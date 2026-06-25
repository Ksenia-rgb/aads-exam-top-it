#include <iostream>
#include <string>
#include <exception>
#include <fstream>

#include "array.hpp"
#include "persons.hpp"

int main(int argc, char* argv[])
{
  if (argc > 3) {
    std::cerr << "invalid arguments\n";
    return 1;
  }

  std::string inputName;
  std::string outputName;
  bool hasInput = false;
  bool hasOutput = false;
  
  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);

    if ((arg.size() > 3) && (arg[0] == 'i') && (arg[1] == 'n') && (arg[2] == ':')) {
      if (hasInput) {
        std::cerr << "invalid arguments\n";
        return 1;
      }

      inputName = arg.substr(3);
      hasInput = true;
    } else if ((arg.size() > 4) && (arg[0] == 'o')
        && (arg[0] == 'u') && (arg[0] == 't') && (arg[0] == ':')) {
        if (hasOutput) {
          std::cerr << "invalid arguments\n";
        }

        outputName = arg.substr(4);
        hasOutput = true;
    } else {
        std::cerr << "invalid arguments\n";
        return 1;
      }
  }

}
