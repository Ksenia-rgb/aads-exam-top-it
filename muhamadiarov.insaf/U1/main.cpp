#include <iostream>
#include <fstream>
#include <limits>
#include <string>

namespace muhamadiarov
{
  struct Person
  {
    size_t id;
    std::string info;
  };
}

int main(int argc, char *argv[])
{
  namespace muh = muhamadiarov;

  if (argc != 2)
  {
    std::cerr << "Incorrect usage\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Can't open file\n";
    return 1;
  }

  int id;
  std::string data;
  try
  {
    while ()
    {
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error loading graph: " << e.what() << '\n';
    return 1;
  }
  file.close();

  return 0;
}
