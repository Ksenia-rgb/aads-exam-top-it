#include "person.hpp"
#include "vector.hpp"
#include <cstddef>
#include <iostream>
#include <string>

bool dirko::containsPerson(const dirko::Vector< dirko::Person > &persons, size_t id)
{
  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].id == id) {
      return true;
    }
  }
  return false;
}

std::istream &dirko::input(std::istream &in, Vector< Person > &persons, size_t &ignored)
{

  ignored = 0;

  std::string line;

  while (std::getline(in, line)) {
    if (line.empty()) {
      continue;
    }

    size_t pos = 0;
    size_t id = 0;

    try {
      id = std::stoul(line, &pos);
    } catch (...) {
      ++ignored;
      continue;
    }

    while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t')) {
      ++pos;
    }

    if (pos == line.size()) {
      ++ignored;
      continue;
    }

    if (containsPerson(persons, id)) {
      ++ignored;
      continue;
    }

    add(persons, {id, line.substr(pos)});
  }
  return in;
}
std::ostream &dirko::output(std::ostream &out, Vector< Person > &persons)
{
  for (size_t i = 0; i < persons.size; ++i) {
    out << persons.data[i].id << ' ' << persons.data[i].info << '\n';
  }
  if (persons.size == 0) {
    out << '\n';
  }
  return out;
}
dirko::Person *dirko::findPersonById(Vector< Person > &persons, size_t id)
{
  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].id == id) {
      return persons.data + i;
    }
  }

  return nullptr;
}

const dirko::Person *dirko::findPersonById(const Vector< Person > &persons, size_t id)
{
  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].id == id) {
      return persons.data + i;
    }
  }

  return nullptr;
}
