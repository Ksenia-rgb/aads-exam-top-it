#include "person.hpp"
#include <iostream>

kuznetsov::Person kuznetsov::readPerson(std::istream& in, bool& success)
{
  size_t id;
  in >> id;
  if (!in) {
    success = false;
    in.clear();
    std::string skip;
    std::getline(in, skip);
    return {};
  }
  while (in.peek() == ' ' || in.peek() == '\t') {
    in.ignore();
  }
  std::string inf;
  std::getline(in, inf);
  if (inf.empty()) {
    success = false;
    return {};
  }
  success = true;
  return Person{id, inf};
}

bool kuznetsov::equalPersons(const Person& a, const Person& b)
{
  bool f = a.id == b.id;
  return f;
}

kuznetsov::darray< kuznetsov::Person > kuznetsov::readArray(std::istream& in, size_t& cSucces, size_t& cFail)
{
  darray< Person > persons = makeDarray< Person >(8);
  in >> std::ws;
  while (!in.eof()) {
    bool s = false;
    Person p = readPerson(in, s);
    if (s && !containsDarray(persons, p, equalPersons)) {
      pushBackDarray(persons, p);
      ++cSucces;
    } else {
      ++cFail;
    }
    in >> std::ws;
  }
  return persons;
}
