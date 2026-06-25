#include "person.hpp"

#include <istream>

namespace muraviev
{
  void initList(PersonList& list)
  {
    list.head = nullptr;
    list.tail = nullptr;
  }

  void clearList(PersonList& list)
  {
    while (list.head != nullptr)
    {
      PersonNode* const next = list.head->next;
      delete list.head;
      list.head = next;
    }
    list.tail = nullptr;
  }

  bool hasPersonId(const PersonList& list, const size_t id)
  {
    PersonNode* current = list.head;
    while (current != nullptr)
    {
      if (current->person.id == id)
      {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  void appendPerson(PersonList& list, const Person& person)
  {
    PersonNode* const node = new PersonNode{person, nullptr};
    if (list.tail == nullptr)
    {
      list.head = node;
    }
    else
    {
      list.tail->next = node;
    }
    list.tail = node;
  }

  bool parsePersonLine(const std::string& line, Person& person)
  {
    if (line.empty() || line[0] < '0' || line[0] > '9')
    {
      return false;
    }
    size_t position = 0;
    size_t id = 0;
    while (position < line.size() && line[position] >= '0' &&
        line[position] <= '9')
    {
      const size_t digit = line[position] - '0';
      id = id * 10 + digit;
      ++position;
    }
    while (position < line.size() &&
        (line[position] == ' ' || line[position] == '\t'))
    {
      ++position;
    }
    if (position == line.size())
    {
      return false;
    }
    person.id = id;
    person.info = line.substr(position);
    return true;
  }

  void readPersons(std::istream& input, PersonList& persons,
      size_t& accepted, size_t& ignored)
  {
    std::string line;
    while (std::getline(input, line))
    {
      Person person;
      if (!parsePersonLine(line, person))
      {
        ++ignored;
      }
      else
      {
        appendPerson(persons, person);
        ++accepted;
      }
    }
  }
}
