#include "records.hpp"

#include <cctype>
#include <cstddef>
#include <istream>
#include <ostream>
#include <string>

namespace {
  bool isSpaceChar(char symbol)
  {
    return std::isspace(static_cast< unsigned char >(symbol)) != 0;
  }

  bool isDigitChar(char symbol)
  {
    return std::isdigit(static_cast< unsigned char >(symbol)) != 0;
  }

  std::string trim(const std::string & text)
  {
    std::size_t begin = 0;
    while (begin < text.size() && isSpaceChar(text[begin])) {
      ++begin;
    }
    std::size_t end = text.size();
    while (end > begin && isSpaceChar(text[end - 1])) {
      --end;
    }
    return text.substr(begin, end - begin);
  }

  bool parsePerson(const std::string & line, samarin::Person & person)
  {
    std::size_t position = 0;
    while (position < line.size() && isSpaceChar(line[position])) {
      ++position;
    }
    const std::size_t base = 10;
    std::size_t id = 0;
    bool hasDigit = false;
    while (position < line.size() && isDigitChar(line[position])) {
      id = id * base + static_cast< std::size_t >(line[position] - '0');
      hasDigit = true;
      ++position;
    }
    if (!hasDigit) {
      return false;
    }
    const std::string info = trim(line.substr(position));
    if (info.empty()) {
      return false;
    }
    person.id = id;
    person.info = info;
    return true;
  }

  bool containsId(const samarin::detail::list_t< samarin::Person > & records, std::size_t id)
  {
    using Node = const samarin::detail::list_node_t< samarin::Person >;
    for (Node * node = records.head; node != nullptr; node = node->next) {
      if (node->value.id == id) {
        return true;
      }
    }
    return false;
  }
}

samarin::counts_t samarin::readRecords(std::istream & input, detail::list_t< Person > & records)
{
  counts_t counts{ 0, 0 };
  std::string line;
  while (std::getline(input, line)) {
    Person person{ 0, "" };
    if (!parsePerson(line, person) || containsId(records, person.id)) {
      ++counts.ignored;
    } else {
      detail::pushBack(records, person);
      ++counts.accepted;
    }
  }
  return counts;
}

void samarin::writeRecords(std::ostream & output, const detail::list_t< Person > & records)
{
  using Node = const detail::list_node_t< Person >;
  for (Node * node = records.head; node != nullptr; node = node->next) {
    output << node->value.id << ' ' << node->value.info << '\n';
  }
}
