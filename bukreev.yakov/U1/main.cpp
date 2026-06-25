#include "list.hpp"
#include <string>

namespace bukreev
{
  struct Person
  {
    size_t id;
    std::string info;
  };
}

int main()
{
  bukreev::List< bukreev::Person >* people;

  bukreev::createList(&people);
  bukreev::deleteList(people);
}
