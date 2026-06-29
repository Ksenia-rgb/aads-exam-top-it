#include "meet.hpp"
#include <fstream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace
{
  struct MeetKey
  {
    size_t id;
    size_t duration;
  };

  bool isLess(const MeetKey &a, const MeetKey &b)
  {
    if (a.id != b.id) {
      return a.id < b.id;
    }

    return a.duration < b.duration;
  }

  void sortMeets(dirko::Vector< MeetKey > &meets)
  {
    for (size_t i = 0; i < meets.size; ++i) {
      for (size_t j = i + 1; j < meets.size; ++j) {
        if (isLess(meets.data[j], meets.data[i])) {
          MeetKey temp = meets.data[i];
          meets.data[i] = meets.data[j];
          meets.data[j] = temp;
        }
      }
    }
  }
}

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

void dirko::cmdRedesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  size_t id = 0;

  input >> id;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  char quote = 0;
  input >> quote;

  if (quote != '"') {
    output << "<INVALID COMMAND>\n";
    return;
  }

  std::string description;

  if (!std::getline(input, description, '"')) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  Person *person = findPersonById(persons, id);

  if (person == nullptr) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  person->info = description;
}

void dirko::cmdDesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  size_t id = 0;

  input >> id;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  const Person *person = findPersonById(persons, id);

  if (person == nullptr) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  if (person->info.empty()) {
    output << "<ANON>\n";
  } else {
    output << person->info << '\n';
  }
}
void dirko::cmdMeets(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t id = 0;

  input >> id;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  Vector< MeetKey > result;
  init(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].first == id) {
      MeetKey key;
      key.id = meets.data[i].second;
      key.duration = meets.data[i].duration;
      add(result, key);
    } else if (meets.data[i].second == id) {
      MeetKey key;
      key.id = meets.data[i].first;
      key.duration = meets.data[i].duration;
      add(result, key);
    }
  }

  sortMeets(result);

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i].id << ' ' << result.data[i].duration << '\n';
  }

  clear(result);
}

void dirko::cmdCommons(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t id1 = 0;
  size_t id2 = 0;

  input >> id1 >> id2;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  Vector< size_t > contacts1;
  Vector< size_t > contacts2;
  Vector< size_t > result;

  init(contacts1);
  init(contacts2);
  init(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].first == id1) {
      add(contacts1, meets.data[i].second);
    } else if (meets.data[i].second == id1) {
      add(contacts1, meets.data[i].first);
    }

    if (meets.data[i].first == id2) {
      add(contacts2, meets.data[i].second);
    } else if (meets.data[i].second == id2) {
      add(contacts2, meets.data[i].first);
    }
  }

  for (size_t i = 0; i < contacts1.size; ++i) {
    bool found = false;

    for (size_t j = 0; j < contacts2.size; ++j) {
      if (contacts1.data[i] == contacts2.data[j]) {
        found = true;
        break;
      }
    }

    if (found) {
      bool duplicate = false;

      for (size_t j = 0; j < result.size; ++j) {
        if (result.data[j] == contacts1.data[i]) {
          duplicate = true;
          break;
        }
      }

      if (!duplicate) {
        add(result, contacts1.data[i]);
      }
    }
  }

  for (size_t i = 0; i < result.size; ++i) {
    for (size_t j = i + 1; j < result.size; ++j) {
      if (result.data[j] < result.data[i]) {
        size_t temp = result.data[i];
        result.data[i] = result.data[j];
        result.data[j] = temp;
      }
    }
  }

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i] << '\n';
  }

  clear(contacts1);
  clear(contacts2);
  clear(result);
}

void dirko::cmdLess(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t time = 0;
  size_t id = 0;

  input >> time >> id;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  Vector< MeetKey > result;
  init(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].first == id && meets.data[i].duration < time) {
      MeetKey key;
      key.id = meets.data[i].second;
      key.duration = meets.data[i].duration;
      add(result, key);
    } else if (meets.data[i].second == id && meets.data[i].duration < time) {
      MeetKey key;
      key.id = meets.data[i].first;
      key.duration = meets.data[i].duration;
      add(result, key);
    }
  }

  sortMeets(result);

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i].id << ' ' << result.data[i].duration << '\n';
  }

  clear(result);
}

void dirko::cmdGreater(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t time = 0;
  size_t id = 0;

  input >> time >> id;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  Vector< MeetKey > result;
  init(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].first == id && meets.data[i].duration > time) {
      MeetKey key;
      key.id = meets.data[i].second;
      key.duration = meets.data[i].duration;
      add(result, key);
    } else if (meets.data[i].second == id && meets.data[i].duration > time) {
      MeetKey key;
      key.id = meets.data[i].first;
      key.duration = meets.data[i].duration;
      add(result, key);
    }
  }

  sortMeets(result);

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i].id << ' ' << result.data[i].duration << '\n';
  }

  clear(result);
}

void dirko::cmdOutPersons(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  std::string filename;

  input >> filename;

  if (!input) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  std::ofstream outputFile(filename);

  if (!outputFile.is_open()) {
    output << "<INVALID COMMAND>\n";
    return;
  }

  Vector< Person > withDescription;
  init(withDescription);

  for (size_t i = 0; i < persons.size; ++i) {
    if (!persons.data[i].info.empty()) {
      add(withDescription, persons.data[i]);
    }
  }

  dirko::output(outputFile, withDescription);

  clear(withDescription);
}
