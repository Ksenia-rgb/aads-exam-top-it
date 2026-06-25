#include "list.hpp"
#include <string>
#include <iostream>

namespace bukreev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  void input(List< Person >* people);
}

int main()
{
  using namespace bukreev;

  List< Person >* people;
  createList(&people);

  try
  {
    input(people);
  }
  catch(std::bad_alloc& e)
  {
    deleteList(people);
    return 3;
  }

  deleteList(people);
}

void bukreev::input(List< Person >* people)
{
  size_t id;
  std::string name;
  while (std::cin >> id >> name)
  {
    insertListTail(people, {id, name});
  }
}
