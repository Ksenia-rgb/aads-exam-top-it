#include <iostream>
#include <string>
#include <fstream>
#include <functions.hpp>
#include <person.hpp>

int main(int argc, char* argv[])
{
  std::string in_name = "";
  std::string out_name = "";

  if (!zubarev::detail::parse_args(argc, argv, in_name, out_name)) {
    return 1;
  }

  std::istream* input = &std::cin;
  std::ifstream in_file;

  if (!in_name.empty()) {
    in_file.open(in_name);
    if (!in_file) {
      return 2;
    }
    input = std::addressof(in_file);
  }

  std::ostream* output = &std::cout;
  std::ofstream out_file;

  if (!out_name.empty()) {
    out_file.open(out_name);
    if (!out_file) {
      return 2;
    }
    output = std::addressof(out_file);
  }

  zubarev::PersonArray persons;
  zubarev::HashSet ids;

  init(persons);
  init(ids);

  size_t ignored = 0;
  size_t correct = 0;
  std::string line;

  while (std::getline(*input, line)) {
    size_t pos = 0;

    while (pos < line.size() && line[pos] == ' ') {
      ++pos;
    }

    size_t id = 0;

    bool hasId = false;

    while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9') {
      hasId = true;

      id = id * 10 + line[pos] - '0';

      ++pos;
    }

    while (pos < line.size() && line[pos] == ' ') {
      ++pos;
    }

    if (!hasId || pos == line.size()) {
      ignored++;
      continue;
    }

    if (zubarev::exists(persons, id)) {
      ignored++;
      continue;
    }

    zubarev::Person person;

    person.id = id;
    person.info = line.substr(pos);

    push(persons, person);

    correct++;
  }

  destroy(persons);
  destroy(ids);
}
