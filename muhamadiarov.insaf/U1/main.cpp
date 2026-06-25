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

  std::istream& getLine(std::istream& in, std::string& str)
   {
    str.clear();

    char ch;
    while (in.get(ch) && (ch == ' ' || ch == '\t'))
    {}

    if (ch == '\n' || !in)
    {
      str.clear();
      return in;
    }
    str.push_back(ch);
    while (in.get(ch) && ch != '\n')
    {
      str.push_back(ch);
    }
    return in;
  }
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
      while (file >> id && muh::getLine(file, data))
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
    while (std::cin >> id && muh::getLine(std::cin, data))
    {
      queue.push({id, data});
    }
  }
  else
  {
    std::cerr << "Incorrect usage\n";
    return 1;
  }

  size_t size = queue.size();
  for (size_t i = 0; i < size; ++i)
  {
    muh::Person& person = queue.top();
    std::cout << person.id << ' ' << person.info << '\n';
    queue.pop();
  }
  return 0;
}
