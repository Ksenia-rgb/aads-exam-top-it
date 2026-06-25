#include <fstream>
#include <iostream>

#include "list.hpp"


int main(int argc, char* argv[])
{
  std::istream* input = &std::cin;

  std::ifstream inFile;

  donkeev::PersonList persons;
  persons.head_ = nullptr;
  persons.tail_ = nullptr;
  persons.size_ = 0;
  
  if (argc > 3)
  {
    std::cerr << "Bad parametrs\n";
    return 1;
  }
  else if (argc == 3)
  {

  }

  int inCount = 0;
  int outCount = 0;

