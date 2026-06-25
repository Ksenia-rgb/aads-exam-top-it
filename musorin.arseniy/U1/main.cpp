#include <iostream>
#include <string>
#include "list.hpp"
#include "person.hpp"
int main()
{
  musorin::List< musorin::Person > records;
  musorin::initList(records);
  std::string line;
  while (std::getline(std::cin, line))
  {
    musorin::Person person{0, ""};
    if (musorin::parseLine(line, person))
    {
      musorin::pushBack(records, person);
    }
  }
  for (const musorin::detail::Node< musorin::Person > * node = records.head;
    node != nullptr; node = node->next)
  {
    std::cout << node->value.id << ' ' << node->value.info << '\n';
  }
  musorin::clear(records);
  return 0;
}
