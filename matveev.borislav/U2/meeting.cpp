#include "meeting.hpp"

#include <fstream>
#include <istream>
#include <limits>
#include <ostream>
#include <string>

namespace
{
  bool isDigit(char symbol)
  {
    return symbol >= '0' && symbol <= '9';
  }

  bool isSpace(char symbol)
  {
    return symbol == ' ' || symbol == '\t';
  }

  void skipSpaces(const std::string &line, size_t &pos)
  {
    while (pos < line.size() && isSpace(line[pos]))
    {
      ++pos;
    }
  }

  bool readSizeT(const std::string &line, size_t &pos, size_t &value)
  {
    skipSpaces(line, pos);

    if (pos == line.size() || !isDigit(line[pos]))
    {
      return false;
    }

    value = 0;

    while (pos < line.size() && isDigit(line[pos]))
    {
      size_t digit = static_cast< size_t >(line[pos] - '0');
      size_t maxValue = std::numeric_limits< size_t >::max();

      if (value > (maxValue - digit) / 10)
      {
        return false;
      }

      value = value * 10 + digit;
      ++pos;
    }

    return true;
  }

  bool readWord(const std::string &line, size_t &pos, std::string &word)
  {
    skipSpaces(line, pos);

    if (pos == line.size())
    {
      return false;
    }

    size_t begin = pos;

    while (pos < line.size() && !isSpace(line[pos]))
    {
      ++pos;
    }

    word = line.substr(begin, pos - begin);
    return true;
  }

  bool isEnd(const std::string &line, size_t &pos)
  {
    skipSpaces(line, pos);
    return pos == line.size();
  }

  bool readDescription(const std::string &line, size_t &pos, std::string &description)
  {
    skipSpaces(line, pos);

    if (pos == line.size() || line[pos] != '"')
    {
      return false;
    }

    ++pos;
    size_t begin = pos;

    while (pos < line.size() && line[pos] != '"')
    {
      ++pos;
    }

    if (pos == line.size())
    {
      return false;
    }

    description = line.substr(begin, pos - begin);
    ++pos;
    return !description.empty();
  }

  bool readMeetingLine(const std::string &line, matveev::Meeting &meeting, bool &ignored)
  {
    ignored = false;

    size_t pos = 0;
    size_t first = 0;
    size_t second = 0;
    size_t duration = 0;

    if (!readSizeT(line, pos, first))
    {
      return false;
    }

    if (!readSizeT(line, pos, second))
    {
      return false;
    }

    if (!readSizeT(line, pos, duration))
    {
      return false;
    }

    skipSpaces(line, pos);

    if (pos != line.size())
    {
      return false;
    }

    if (first == second)
    {
      ignored = true;
      return true;
    }

    meeting.first = first;
    meeting.second = second;
    meeting.duration = duration;
    return true;
  }

  void writeAnons(std::ostream &out, const matveev::Array< matveev::Person > &persons)
  {
    bool hasPrevious = false;
    size_t previous = 0;

    while (true)
    {
      bool found = false;
      size_t next = 0;

      for (size_t i = 0; i < persons.size; ++i)
      {
        if (!persons.data[i].info.empty())
        {
          continue;
        }

        if (hasPrevious && persons.data[i].id <= previous)
        {
          continue;
        }

        if (!found || persons.data[i].id < next)
        {
          next = persons.data[i].id;
          found = true;
        }
      }

      if (!found)
      {
        break;
      }

      out << next << '\n';
      previous = next;
      hasPrevious = true;
    }
  }
}

bool matveev::readMeetings(std::istream &input, Array< Meeting > &meetings)
{
  std::string line;

  while (std::getline(input, line))
  {
    if (line.empty())
    {
      return false;
    }

    Meeting meeting;
    bool ignored = false;

    if (!readMeetingLine(line, meeting, ignored))
    {
      return false;
    }

    if (!ignored)
    {
      pushBack(meetings, meeting);
    }
  }

  return true;
}

bool matveev::readPersons(std::istream &input, Array< Person > &persons)
{
  while (input)
  {
    Person person;
    bool valid = false;

    if (!readPerson(input, person, valid))
    {
      return !input.bad();
    }

    if (valid && findPersonIndex(persons, person.id) == persons.size)
    {
      pushBack(persons, person);
    }
  }

  return !input.bad();
}

size_t matveev::findPersonIndex(const Array< Person > &persons, size_t id)
{
  for (size_t i = 0; i < persons.size; ++i)
  {
    if (persons.data[i].id == id)
    {
      return i;
    }
  }

  return persons.size;
}

void matveev::addMeetingPersons(const Array< Meeting > &meetings, Array< Person > &persons)
{
  for (size_t i = 0; i < meetings.size; ++i)
  {
    if (findPersonIndex(persons, meetings.data[i].first) == persons.size)
    {
      Person person;
      person.id = meetings.data[i].first;
      person.info.clear();
      pushBack(persons, person);
    }

    if (findPersonIndex(persons, meetings.data[i].second) == persons.size)
    {
      Person person;
      person.id = meetings.data[i].second;
      person.info.clear();
      pushBack(persons, person);
    }
  }
}

bool matveev::executePersonCommand(const std::string &line, Array< Person > &persons, std::ostream &out)
{
  size_t pos = 0;
  std::string command;

  if (!readWord(line, pos, command))
  {
    return false;
  }

  if (command == "anons")
  {
    if (!isEnd(line, pos))
    {
      return false;
    }

    writeAnons(out, persons);
    return true;
  }

  if (command == "desc")
  {
    size_t id = 0;

    if (!readSizeT(line, pos, id) || !isEnd(line, pos))
    {
      return false;
    }

    size_t index = findPersonIndex(persons, id);

    if (index == persons.size)
    {
      return false;
    }

    if (persons.data[index].info.empty())
    {
      out << "<ANON>\n";
    }
    else
    {
      out << persons.data[index].info << '\n';
    }

    return true;
  }

  if (command == "redesc")
  {
    size_t id = 0;
    std::string description;

    if (!readSizeT(line, pos, id) || !readDescription(line, pos, description) || !isEnd(line, pos))
    {
      return false;
    }

    size_t index = findPersonIndex(persons, id);

    if (index == persons.size)
    {
      return false;
    }

    persons.data[index].info = description;
    return true;
  }

  if (command == "out-persons")
  {
    std::string filename;

    if (!readWord(line, pos, filename) || !isEnd(line, pos))
    {
      return false;
    }

    std::ofstream output(filename);

    if (!output)
    {
      return false;
    }

    for (size_t i = 0; i < persons.size; ++i)
    {
      if (!persons.data[i].info.empty())
      {
        writePerson(output, persons.data[i]) << '\n';
      }
    }

    return static_cast< bool >(output);
  }

  return false;
}
