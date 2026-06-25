#include "io.hpp"

#include <cctype>
#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include <utility>

namespace {
  using PersonNode = samarin::detail::list_node_t< samarin::person_t >;

  bool isSpaceChar(char symbol)
  {
    return std::isspace(static_cast< unsigned char >(symbol)) != 0;
  }

  bool isDigitChar(char symbol)
  {
    return std::isdigit(static_cast< unsigned char >(symbol)) != 0;
  }

  void skipSpaces(const std::string & text, std::size_t & position)
  {
    while (position < text.size() && isSpaceChar(text[position])) {
      ++position;
    }
  }

  std::string trim(const std::string & text)
  {
    std::size_t begin = 0;
    skipSpaces(text, begin);
    std::size_t end = text.size();
    while (end > begin && isSpaceChar(text[end - 1])) {
      --end;
    }
    return text.substr(begin, end - begin);
  }

  std::pair< bool, std::size_t > parseId(const std::string & line, std::size_t & position)
  {
    const std::size_t base = 10;
    std::size_t id = 0;
    bool hasDigit = false;
    while (position < line.size() && isDigitChar(line[position])) {
      id = id * base + static_cast< std::size_t >(line[position] - '0');
      hasDigit = true;
      ++position;
    }
    return std::make_pair(hasDigit, id);
  }

  bool parsePerson(const std::string & line, std::size_t & id, std::string & description)
  {
    std::size_t position = 0;
    skipSpaces(line, position);
    const std::pair< bool, std::size_t > parsed = parseId(line, position);
    if (!parsed.first) {
      return false;
    }
    const std::string info = trim(line.substr(position));
    if (info.empty()) {
      return false;
    }
    id = parsed.second;
    description = info;
    return true;
  }
}

void samarin::readPersons(std::istream & input, dataset_t & data)
{
  std::string line;
  while (std::getline(input, line)) {
    std::size_t id = 0;
    std::string description;
    if (parsePerson(line, id, description)) {
      insertPerson(data, id, true, description);
    }
  }
}

bool samarin::readMeetings(std::istream & input, dataset_t & data)
{
  while (true) {
    std::size_t first = 0;
    if (!(input >> first)) {
      break;
    }
    std::size_t second = 0;
    std::size_t duration = 0;
    if (!(input >> second >> duration)) {
      return false;
    }
    addMeeting(data, first, second, duration);
  }
  return input.eof();
}

void samarin::writePersons(std::ostream & output, const dataset_t & data)
{
  for (const PersonNode * node = data.persons.head; node != nullptr; node = node->next) {
    if (node->value.named) {
      output << node->value.id << ' ' << node->value.description << '\n';
    }
  }
}
