#include "commands.hpp"

#include <cctype>
#include <cstddef>
#include <istream>
#include <ostream>
#include <string>

namespace {
  using PersonNode = samarin::detail::list_node_t< samarin::person_t >;

  bool isSpaceChar(char symbol)
  {
    return std::isspace(static_cast< unsigned char >(symbol)) != 0;
  }

  void printInvalid(std::ostream & out)
  {
    out << "<INVALID COMMAND>\n";
  }

  std::string nextWord(const std::string & line, std::size_t & position)
  {
    while (position < line.size() && isSpaceChar(line[position])) {
      ++position;
    }
    const std::size_t start = position;
    while (position < line.size() && !isSpaceChar(line[position])) {
      ++position;
    }
    return line.substr(start, position - start);
  }

  bool parseNumber(const std::string & token, std::size_t & value)
  {
    if (token.empty()) {
      return false;
    }
    const std::size_t base = 10;
    std::size_t result = 0;
    for (std::size_t i = 0; i < token.size(); ++i) {
      const char symbol = token[i];
      if (std::isdigit(static_cast< unsigned char >(symbol)) == 0) {
        return false;
      }
      result = result * base + static_cast< std::size_t >(symbol - '0');
    }
    value = result;
    return true;
  }

  void doAnons(std::ostream & out, const samarin::dataset_t & data)
  {
    for (const PersonNode * node = data.persons.head; node != nullptr; node = node->next) {
      if (!node->value.named) {
        out << node->value.id << '\n';
      }
    }
  }

  void doDesc(std::ostream & out, samarin::dataset_t & data, std::size_t id)
  {
    const samarin::person_t * const person = samarin::findPerson(data, id);
    if (person == nullptr) {
      printInvalid(out);
    } else if (person->named) {
      out << person->description << '\n';
    } else {
      out << "<ANON>\n";
    }
  }

  void executeLine(std::ostream & out, samarin::dataset_t & data, const std::string & line)
  {
    std::size_t position = 0;
    const std::string command = nextWord(line, position);
    if (command.empty()) {
      return;
    }
    if (command == "anons") {
      doAnons(out, data);
    } else if (command == "desc") {
      std::size_t id = 0;
      if (parseNumber(nextWord(line, position), id)) {
        doDesc(out, data, id);
      } else {
        printInvalid(out);
      }
    } else {
      printInvalid(out);
    }
  }
}

void samarin::runCommands(std::istream & input, std::ostream & output, dataset_t & data)
{
  std::string line;
  while (std::getline(input, line)) {
    executeLine(output, data, line);
  }
}
