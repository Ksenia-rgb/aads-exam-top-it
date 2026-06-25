#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
#include "queue.hpp"

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
  
  size_t id;
  std::string data;
  muh::Queue< muh::Person > queue;
  if (argc == 2)
  { 
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Can't open file\n";
      return 1;
    }

    try
    {
      while (file >> id >> data)
      {
        queue.push({id, data});
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << "Incorrect data: " << e.what() << '\n';
      return 1;
    }
    file.close();
  }
  else if (argc == 1)
  {
    while (std::cin >> id >> data)
    {
      queue.push({id, data});
    }
  }
  else
  {
    std::cerr << "Incorrect usage\n";
    return 1;
  }

  for (size_t i = 0; i < queue.size(); ++i)
  {
    muh::Person& person = queue.top();
    std::cout << person.id << ' ' << person.info << '\n';
    queue.pop();
  }
  return 0;
}
