#include "options.hpp"
#include "person.hpp"

#include <iostream>

int main(int argc, char** argv)
{
  const size_t argumentCount = argc;
  muraviev::ProgramOptions options;
  if (!muraviev::parseProgramOptions(argumentCount, argv, options))
  {
    return 1;
  }
  muraviev::PersonList persons;
  muraviev::initList(persons);
  size_t accepted = 0;
  size_t ignored = 0;
  muraviev::readPersons(std::cin, persons, accepted, ignored);

  muraviev::PersonNode* current = persons.head;
  while (current != nullptr)
  {
    std::cout << current->person.id << ' ' << current->person.info << '\n';
    current = current->next;
  }
  std::cerr << accepted << ' ' << ignored << '\n';
  muraviev::clearList(persons);
  return 0;
}
