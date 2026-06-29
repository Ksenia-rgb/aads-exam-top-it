#include <cstddef>
#include <iostream>
#include "commands.hpp"

void lavrentev::desc(Person** persons, size_t id)
{
  if (persons[id]->info != "")
  {
    std::cout << persons[id]->info << "\n";
  }
  else
  {
    std::cout << "<ANON>\n";
  }
}
