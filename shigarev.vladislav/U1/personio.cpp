#include "personio.hpp"

#include <iostream>
#include <string>
#include <limits>
#include <cctype>

namespace {
  bool isBlank(char ch)
  {
    return ch != '\n'
        && std::isspace(static_cast< unsigned char >(ch));
  }

  size_t skipBlanks(const std::string& line, size_t pos)
  {
    while (pos < line.size() && isBlank(line[pos])) {
      ++pos;
    }
    return pos;
  }

  bool parseId(const std::string& line,
      size_t& pos, size_t& id)
  {
    pos = skipBlanks(line, pos);
    if (pos >= line.size()) {
      return false;
    }
    const unsigned char first = static_cast< unsigned char >(line[pos]);
    if (!std::isdigit(first)) {
      return false;
    }
    const size_t maxVal = std::numeric_limits< size_t >::max();
    size_t result = 0;
    while (pos < line.size()) {
      const unsigned char ch = static_cast< unsigned char >(line[pos]);
      if (!std::isdigit(ch)) {
        break;
      }
      const size_t digit = static_cast< size_t >(line[pos] - '0');
      if (result > (maxVal - digit) / 10) {
        return false;
      }
      result = result * 10 + digit;
      ++pos;
    }
    id = result;
    return true;
  }

  bool parsePerson(const std::string& line,
      shigarev::Person& person)
  {
    size_t pos = 0;
    size_t id = 0;
    if (!parseId(line, pos, id)) {
      return false;
    }
    pos = skipBlanks(line, pos);
    if (pos >= line.size()) {
      return false;
    }
    person.id = id;
    person.info = line.substr(pos);
    return true;
  }

  std::string stripCr(const std::string& line)
  {
    if (!line.empty() && line.back() == '\r') {
      return line.substr(0, line.size() - 1);
    }
    return line;
  }

  bool hasDuplicateId(
      const shigarev::DynArray< shigarev::Person >& arr,
      size_t id)
  {
    return shigarev::contains(arr,
        [id](const shigarev::Person& p)
        {
          return p.id == id;
        });
  }
}

shigarev::ReadResult shigarev::readPersons(std::istream& in)
{
  ReadResult result = {createDynArray< Person >(8), 0, 0};
  std::string line = "";
  while (std::getline(in, line)) {
    const std::string cleaned = stripCr(line);
    Person person = {0, ""};
    if (!parsePerson(cleaned, person)) {
      ++result.ignoredCount;
      continue;
    }
    if (hasDuplicateId(result.persons, person.id)) {
      ++result.ignoredCount;
      continue;
    }
    pushBack(result.persons, std::move(person));
    ++result.readCount;
  }
  return result;
}

void shigarev::writePersons(std::ostream& out,
    const DynArray< Person >& persons)
{
  for (size_t i = 0; i < persons.size_; ++i) {
    const Person& p = getAt(persons, i);
    out << p.id << " " << p.info << "\n";
  }
}

void shigarev::writeStats(std::ostream& err,
    size_t read, size_t ignored)
{
  err << read << " " << ignored << "\n";
}
