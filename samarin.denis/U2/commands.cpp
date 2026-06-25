#include "commands.hpp"

#include <cstddef>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <utility>

#include "io.hpp"
#include "parsing.hpp"

namespace {
  using PersonNode = samarin::detail::list_node_t< samarin::Person >;
  using MeetingNode = samarin::detail::list_node_t< samarin::Meeting >;
  using DurationPair = std::pair< std::size_t, std::size_t >;
  using PairNode = samarin::detail::list_node_t< DurationPair >;

  enum class Bound {
    none,
    below,
    above
  };

  void printInvalid(std::ostream & out)
  {
    out << "<INVALID COMMAND>\n";
  }

  std::string nextWord(const std::string & line, std::size_t & position)
  {
    while (position < line.size() && samarin::detail::isSpaceChar(line[position])) {
      ++position;
    }
    const std::size_t start = position;
    while (position < line.size() && !samarin::detail::isSpaceChar(line[position])) {
      ++position;
    }
    return line.substr(start, position - start);
  }

  bool parseNumber(const std::string & token, std::size_t & value)
  {
    std::size_t position = 0;
    const std::pair< bool, std::size_t > parsed = samarin::detail::readUnsigned(token, position);
    if (!parsed.first || position != token.size()) {
      return false;
    }
    value = parsed.second;
    return true;
  }

  bool parseOne(const std::string & line, std::size_t & position, std::size_t & value)
  {
    return parseNumber(nextWord(line, position), value);
  }

  bool parseTwo(const std::string & line, std::size_t & position, std::size_t & first,
      std::size_t & second)
  {
    return parseOne(line, position, first) && parseOne(line, position, second);
  }

  bool parseQuoted(const std::string & line, std::size_t & position, std::string & value)
  {
    while (position < line.size() && line[position] != '"') {
      ++position;
    }
    if (position >= line.size()) {
      return false;
    }
    ++position;
    const std::size_t start = position;
    while (position < line.size() && line[position] != '"') {
      ++position;
    }
    if (position >= line.size()) {
      return false;
    }
    value = line.substr(start, position - start);
    ++position;
    return true;
  }

  bool meetingComesBefore(const DurationPair & left, const DurationPair & right)
  {
    if (left.first != right.first) {
      return left.first < right.first;
    }
    return left.second <= right.second;
  }

  void printMeetings(std::ostream & out, const samarin::Dataset & data, std::size_t id,
      Bound bound, std::size_t threshold)
  {
    samarin::detail::list_t< DurationPair > selected{ nullptr, nullptr };
    for (const MeetingNode * node = data.meetings.head; node != nullptr; node = node->next) {
      const samarin::Meeting & meeting = node->value;
      std::size_t partner = 0;
      if (meeting.first == id) {
        partner = meeting.second;
      } else if (meeting.second == id) {
        partner = meeting.first;
      } else {
        continue;
      }
      const bool keep = (bound == Bound::none)
          || (bound == Bound::below && meeting.duration < threshold)
          || (bound == Bound::above && meeting.duration > threshold);
      if (keep) {
        const DurationPair entry = std::make_pair(partner, meeting.duration);
        samarin::detail::insertSorted(selected, entry, meetingComesBefore);
      }
    }
    for (const PairNode * node = selected.head; node != nullptr; node = node->next) {
      out << node->value.first << ' ' << node->value.second << '\n';
    }
    samarin::detail::clear(selected);
  }

  void doAnons(std::ostream & out, const samarin::Dataset & data)
  {
    for (const PersonNode * node = data.persons.head; node != nullptr; node = node->next) {
      if (!node->value.named) {
        out << node->value.id << '\n';
      }
    }
  }

  void doDesc(std::ostream & out, samarin::Dataset & data, std::size_t id)
  {
    const samarin::Person * const person = samarin::findPerson(data, id);
    if (person == nullptr) {
      printInvalid(out);
    } else if (person->named) {
      out << person->description << '\n';
    } else {
      out << "<ANON>\n";
    }
  }

  void doRedesc(std::ostream & out, samarin::Dataset & data, std::size_t id,
      const std::string & description)
  {
    samarin::Person * const person = samarin::findPerson(data, id);
    if (person == nullptr) {
      printInvalid(out);
      return;
    }
    person->description = description;
    person->named = true;
  }

  void doMeets(std::ostream & out, samarin::Dataset & data, std::size_t id)
  {
    if (samarin::findPerson(data, id) == nullptr) {
      printInvalid(out);
      return;
    }
    printMeetings(out, data, id, Bound::none, 0);
  }

  void doBounded(std::ostream & out, samarin::Dataset & data, std::size_t threshold,
      std::size_t id, Bound bound)
  {
    if (samarin::findPerson(data, id) == nullptr) {
      printInvalid(out);
      return;
    }
    printMeetings(out, data, id, bound, threshold);
  }

  bool metWith(const samarin::Dataset & data, std::size_t person, std::size_t partner)
  {
    const auto matches = [person, partner](const samarin::Meeting & meeting)
    {
      return (meeting.first == person && meeting.second == partner)
          || (meeting.first == partner && meeting.second == person);
    };
    return samarin::detail::findValue(data.meetings, matches) != nullptr;
  }

  void doCommons(std::ostream & out, samarin::Dataset & data, std::size_t first, std::size_t second)
  {
    const bool bothExist = samarin::findPerson(data, first) != nullptr
        && samarin::findPerson(data, second) != nullptr;
    if (!bothExist) {
      printInvalid(out);
      return;
    }
    for (const PersonNode * node = data.persons.head; node != nullptr; node = node->next) {
      const std::size_t candidate = node->value.id;
      if (metWith(data, first, candidate) && metWith(data, second, candidate)) {
        out << candidate << '\n';
      }
    }
  }

  void doDeanon(std::ostream & out, samarin::Dataset & data, std::size_t anonId,
      std::size_t namedId)
  {
    samarin::Person * const anon = samarin::findPerson(data, anonId);
    samarin::Person * const named = samarin::findPerson(data, namedId);
    if (anon == nullptr || named == nullptr || anon->named || !named->named || anonId == namedId) {
      printInvalid(out);
      return;
    }
    for (MeetingNode * node = data.meetings.head; node != nullptr; node = node->next) {
      if (node->value.first == anonId) {
        node->value.first = namedId;
      }
      if (node->value.second == anonId) {
        node->value.second = namedId;
      }
    }
    const auto isSelfMeeting = [](const samarin::Meeting & meeting)
    {
      return meeting.first == meeting.second;
    };
    samarin::detail::removeIf(data.meetings, isSelfMeeting);
    const auto hasAnonId = [anonId](const samarin::Person & person)
    {
      return person.id == anonId;
    };
    samarin::detail::removeIf(data.persons, hasAnonId);
  }

  void doOutPersons(std::ostream & out, const samarin::Dataset & data, const std::string & filename)
  {
    std::ofstream file(filename);
    if (!file.is_open()) {
      printInvalid(out);
      return;
    }
    samarin::writePersons(file, data);
  }

  void executeLine(std::ostream & out, samarin::Dataset & data, const std::string & line)
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
      if (parseOne(line, position, id)) {
        doDesc(out, data, id);
      } else {
        printInvalid(out);
      }
    } else if (command == "redesc") {
      std::size_t id = 0;
      std::string description;
      if (parseOne(line, position, id) && parseQuoted(line, position, description)) {
        doRedesc(out, data, id, description);
      } else {
        printInvalid(out);
      }
    } else if (command == "meets") {
      std::size_t id = 0;
      if (parseOne(line, position, id)) {
        doMeets(out, data, id);
      } else {
        printInvalid(out);
      }
    } else if (command == "less") {
      std::size_t threshold = 0;
      std::size_t id = 0;
      if (parseTwo(line, position, threshold, id)) {
        doBounded(out, data, threshold, id, Bound::below);
      } else {
        printInvalid(out);
      }
    } else if (command == "greater") {
      std::size_t threshold = 0;
      std::size_t id = 0;
      if (parseTwo(line, position, threshold, id)) {
        doBounded(out, data, threshold, id, Bound::above);
      } else {
        printInvalid(out);
      }
    } else if (command == "commons") {
      std::size_t first = 0;
      std::size_t second = 0;
      if (parseTwo(line, position, first, second)) {
        doCommons(out, data, first, second);
      } else {
        printInvalid(out);
      }
    } else if (command == "deanon") {
      std::size_t anonId = 0;
      std::size_t namedId = 0;
      if (parseTwo(line, position, anonId, namedId)) {
        doDeanon(out, data, anonId, namedId);
      } else {
        printInvalid(out);
      }
    } else if (command == "out-persons") {
      const std::string filename = nextWord(line, position);
      if (filename.empty()) {
        printInvalid(out);
      } else {
        doOutPersons(out, data, filename);
      }
    } else {
      printInvalid(out);
    }
  }
}

void samarin::runCommands(std::istream & input, std::ostream & output, Dataset & data)
{
  std::string line;
  while (std::getline(input, line)) {
    executeLine(output, data, line);
  }
}
