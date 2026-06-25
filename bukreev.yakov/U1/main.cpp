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

  size_t input(List< Person >* people);
  void output(List< Person >* people);
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

  output(people);
  deleteList(people);
}

size_t bukreev::input(List< Person >* people)
{
  size_t goodEntries = 0;

  size_t id;
  std::string name;
  while (std::cin >> id >> name)
  {
    insertListTail(people, {id, name});
    goodEntries++;
  }

  return goodEntries;
}

void bukreev::output(List< Person >* people)
{
  List< Person >* h = people->next;
  while (h != people)
  {
    Person& p = h->val;
    std::cout << p.id << ' ' << p.info << '\n';

    h = h->next;
  }
}
