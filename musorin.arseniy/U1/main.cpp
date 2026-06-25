#include <iostream>
#include <string>
#include "list.hpp"
#include "person.hpp"
namespace
{
bool hasId(const musorin::List< musorin::Person > & records, std::size_t id)
{
  for (const musorin::detail::Node< musorin::Person > * node = records.head;
    node != nullptr; node = node->next)
  {
    if (node->value.id == id)
    {
      return true;
    }
  }
  return false;
}
}
int main()
{
  musorin::List< musorin::Person > records;
  musorin::initList(records);
  std::size_t accepted = 0;
  std::size_t ignored = 0;
  std::string line;
  while (std::getline(std::cin, line))
  {
    musorin::Person person{0, ""};
    if (!musorin::parseLine(line, person))
    {
      ++ignored;
      continue;
    }
    if (hasId(records, person.id))
    {
      ++ignored;
      continue;
    }
    musorin::pushBack(records, person);
    ++accepted;
  }
  for (const musorin::detail::Node< musorin::Person > * node = records.head;
    node != nullptr; node = node->next)
  {
    std::cout << node->value.id << ' ' << node->value.info << '\n';
  }
  std::cerr << accepted << ' ' << ignored << '\n';
  musorin::clear(records);
  return 0;
}
