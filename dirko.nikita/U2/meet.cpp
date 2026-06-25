#include "meet.hpp"
#include <fstream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

void dirko::readMeets(std::istream &input, Vector< Meet > &meets)
{
  std::string line;

  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    size_t pos = 0;
    size_t first = 0;
    size_t second = 0;
    size_t duration = 0;

    try {
      first = std::stoul(line, &pos);
    } catch (...) {
      throw std::runtime_error("Invalid meet data");
    }

    while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t')) {
      ++pos;
    }

    if (pos == line.size()) {
      throw std::runtime_error("Invalid meet data");
    }

    try {
      second = std::stoul(line.substr(pos), &pos);
    } catch (...) {
      throw std::runtime_error("Invalid meet data");
    }

    while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t')) {
      ++pos;
    }

    if (pos == line.size()) {
      throw std::runtime_error("Invalid meet data");
    }

    try {
      duration = std::stoul(line.substr(pos), &pos);
    } catch (...) {
      throw std::runtime_error("Invalid meet data");
    }

    Meet meet;
    meet.first = first;
    meet.second = second;
    meet.duration = duration;

    add(meets, meet);
  }
}

void dirko::removeSelfMeets(Vector< Meet > &meets)
{
  Vector< Meet > filtered;
  init(filtered);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].first != meets.data[i].second) {
      add(filtered, meets.data[i]);
    }
  }

  clear(meets);
  meets = filtered;
}

void dirko::cmdAnons(std::istream &, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  Vector< size_t > anons;
  init(anons);

  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].info.empty()) {
      add(anons, persons.data[i].id);
    }
  }

  for (size_t i = 0; i < anons.size; ++i) {
    for (size_t j = i + 1; j < anons.size; ++j) {
      if (anons.data[j] < anons.data[i]) {
        size_t temp = anons.data[i];
        anons.data[i] = anons.data[j];
        anons.data[j] = temp;
      }
    }
  }

  for (size_t i = 0; i < anons.size; ++i) {
    output << anons.data[i] << '\n';
  }

  clear(anons);
}

void dirko::cmdDeanon(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &meets)
{
  size_t anonId = 0;
  size_t id = 0;

  input >> anonId >> id;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  const Person *anon = findPersonById(persons, anonId);

  if (anon == nullptr || !anon->info.empty()) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  const Person *target = findPersonById(persons, id);

  if (target == nullptr || target->info.empty()) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].first == anonId) {
      meets.data[i].first = id;
    }

    if (meets.data[i].second == anonId) {
      meets.data[i].second = id;
    }
  }

  Vector< Person > newPersons;
  init(newPersons);

  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].id != anonId) {
      add(newPersons, persons.data[i]);
    }
  }

  clear(persons);
  persons = newPersons;

  removeSelfMeets(meets);
}
