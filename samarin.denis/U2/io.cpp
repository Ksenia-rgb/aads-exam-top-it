#include "io.hpp"

#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include <utility>

#include "parsing.hpp"

namespace {
  using PersonNode = samarin::detail::list_node_t< samarin::Person >;

  void skipSpaces(const std::string & text, std::size_t & position)
  {
    while (position < text.size() && samarin::detail::isSpaceChar(text[position])) {
      ++position;
    }
  }

  bool readField(const std::string & line, std::size_t & position, std::size_t & value)
  {
    skipSpaces(line, position);
    const std::pair< bool, std::size_t > parsed = samarin::detail::readUnsigned(line, position);
    if (!parsed.first) {
      return false;
    }
    value = parsed.second;
    return true;
  }
}

void samarin::readPersons(std::istream & input, Dataset & data)
{
  std::string line;
  while (std::getline(input, line)) {
    std::size_t id = 0;
    std::string description;
    if (detail::parseRecord(line, id, description)) {
      insertPerson(data, id, true, description);
    }
  }
}

bool samarin::readMeetings(std::istream & input, Dataset & data)
{
  std::string line;
  while (std::getline(input, line)) {
    std::size_t position = 0;
    skipSpaces(line, position);
    if (position == line.size()) {
      continue;
    }
    std::size_t first = 0;
    std::size_t second = 0;
    std::size_t duration = 0;
    if (!readField(line, position, first) || !readField(line, position, second)
        || !readField(line, position, duration)) {
      return false;
    }
    skipSpaces(line, position);
    if (position != line.size()) {
      return false;
    }
    addMeeting(data, first, second, duration);
  }
  return true;
}

void samarin::writePersons(std::ostream & output, const Dataset & data)
{
  for (const PersonNode * node = data.persons.head; node != nullptr; node = node->next) {
    if (node->value.named) {
      output << node->value.id << ' ' << node->value.description << '\n';
    }
  }
}
