#include "person_io.hpp"

#include <iostream>

int main(int argc, char** argv)
{
  return alekseev::runPersonInput(argc, argv, std::cin, std::cout, std::cerr);
}
