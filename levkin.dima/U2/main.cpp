#include <iostream>
#include <fstream>
#include <string>
#include "db.hpp"
#include "commands.hpp"
#include "utils.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2 || argc > 3) {
    std::cerr << "Error: Invalid number of arguments.\n";
    return 1;
  }
  std::string data_file;
  std::string in_file;

  using namespace levkin;
  if (!parseArguments(argc, argv, data_file, in_file)) {
    return 1;
  }
  
}
