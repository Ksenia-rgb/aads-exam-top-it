#include "list.hpp"
#include <string>

struct Person
{
  size_t id;
  std::string info;
};

bukreev::List< Person >* people;

int main()
{
  bukreev::createList(&people);
  bukreev::deleteList(people);
}
