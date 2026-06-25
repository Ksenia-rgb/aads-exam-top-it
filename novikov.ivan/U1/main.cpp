#include <person.hpp>
#include <parse.hpp>
#include <fstream>

int main(int argc, char* argv[])
{
  if (argc > 3)
  {
    std::cerr << "Too many arguments" << '\n';
    return 0;
  }

  std::string in_name = "";
  std::string out_name = "";

  if (!novikov::parse(argc, argv, in_name, out_name)) {
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

  novikov::PersonArray persons;
  novikov::IdSet ids;

  create(persons);
  create(ids);

  size_t ignored = 0;
  size_t correct = 0;
  std::string line;

  while (std::getline(*input, line)) {
    size_t pos = 0;

    while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos]))) {
      ++pos;
    }

    if (pos == line.size()) {
      continue;
    }

    size_t id = 0;

    bool hasId = false;

    while (pos < line.size() && std::isdigit(static_cast< unsigned char >(line[pos]))) {
      hasId = true;
      id = id * 10 + line[pos] - '0';
      ++pos;
    }

    if (!hasId) {
      ++ignored;
      continue;
    }

    if (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos]))) {
      ++ignored;
      continue;
    }

    while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos]))) {
      ++pos;
    }

    if (pos == line.size()) {
      ++ignored;
      continue;
    }

    if (novikov::contains(ids, id)) {
      ++ignored;
      continue;
    }

    novikov::Person person;

    person.id = id;
    person.info = line.substr(pos);

    novikov::push(persons, person);

    novikov::insert(ids, id);

    ++correct;
  }

  std::ostream* output = &std::cout;
  std::ofstream out_file;

  if (!out_name.empty()) {
    out_file.open(out_name);

    if (!out_file) {
      drop(persons);
      drop(ids);

      return 2;
    }

    output = std::addressof(out_file);
  }

  for (size_t i = 0; i < persons.size; ++i) {
    *output << persons.data[i].id << " " << persons.data[i].info << '\n';
  }

  if (persons.size == 0) {
    *output << '\n';
  }

  std::cerr << correct << " " << ignored << '\n';

  drop(persons);
  drop(ids);

  return 0;
}
