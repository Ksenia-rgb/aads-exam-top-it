#include "commands.hpp"

#include <cstddef>
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

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

  bool isBefore(const DurationPair & value, std::size_t partner, std::size_t duration)
  {
    if (value.first != partner) {
      return value.first < partner;
    }
    return value.second <= duration;
  }

  void insertMeeting(samarin::detail::list_t< DurationPair > & list, std::size_t partner,
      std::size_t duration)
  {
    PairNode ** link = std::addressof(list.head);
    while (*link != nullptr && isBefore((*link)->value, partner, duration)) {
      link = std::addressof((*link)->next);
    }
    PairNode * const node = new PairNode{ std::make_pair(partner, duration), *link };
    *link = node;
    if (node->next == nullptr) {
      list.tail = node;
    }
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
        insertMeeting(selected, partner, meeting.duration);
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
    for (const MeetingNode * node = data.meetings.head; node != nullptr; node = node->next) {
      const samarin::Meeting & meeting = node->value;
      if ((meeting.first == person && meeting.second == partner)
          || (meeting.first == partner && meeting.second == person)) {
        return true;
      }
    }
    return false;
  }

  void doCommons(std::ostream & out, samarin::Dataset & data, std::size_t first, std::size_t second)
  {
    if (samarin::findPerson(data, first) == nullptr || samarin::findPerson(data, second) == nullptr) {
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

  void removeSelfMeetings(samarin::Dataset & data)
  {
    MeetingNode ** link = std::addressof(data.meetings.head);
    MeetingNode * tail = nullptr;
    while (*link != nullptr) {
      if ((*link)->value.first == (*link)->value.second) {
        MeetingNode * const dead = *link;
        *link = dead->next;
        delete dead;
      } else {
        tail = *link;
        link = std::addressof((*link)->next);
      }
    }
    data.meetings.tail = tail;
  }

  void removePerson(samarin::Dataset & data, std::size_t id)
  {
    PersonNode ** link = std::addressof(data.persons.head);
    PersonNode * tail = nullptr;
    while (*link != nullptr) {
      if ((*link)->value.id == id) {
        PersonNode * const dead = *link;
        *link = dead->next;
        delete dead;
      } else {
        tail = *link;
        link = std::addressof((*link)->next);
      }
    }
    data.persons.tail = tail;
  }

  void doDeanon(std::ostream & out, samarin::Dataset & data, std::size_t anonId, std::size_t namedId)
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
    removeSelfMeetings(data);
    removePerson(data, anonId);
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
      if (parseNumber(nextWord(line, position), id)) {
        doDesc(out, data, id);
      } else {
        printInvalid(out);
      }
    } else if (command == "redesc") {
      std::size_t id = 0;
      std::string description;
      if (parseNumber(nextWord(line, position), id) && parseQuoted(line, position, description)) {
        doRedesc(out, data, id, description);
      } else {
        printInvalid(out);
      }
    } else if (command == "meets") {
      std::size_t id = 0;
      if (parseNumber(nextWord(line, position), id)) {
        doMeets(out, data, id);
      } else {
        printInvalid(out);
      }
    } else if (command == "less") {
      std::size_t threshold = 0;
      std::size_t id = 0;
      if (parseNumber(nextWord(line, position), threshold) && parseNumber(nextWord(line, position), id)) {
        doBounded(out, data, threshold, id, Bound::below);
      } else {
        printInvalid(out);
      }
    } else if (command == "greater") {
      std::size_t threshold = 0;
      std::size_t id = 0;
      if (parseNumber(nextWord(line, position), threshold) && parseNumber(nextWord(line, position), id)) {
        doBounded(out, data, threshold, id, Bound::above);
      } else {
        printInvalid(out);
      }
    } else if (command == "commons") {
      std::size_t first = 0;
      std::size_t second = 0;
      if (parseNumber(nextWord(line, position), first) && parseNumber(nextWord(line, position), second)) {
        doCommons(out, data, first, second);
      } else {
        printInvalid(out);
      }
    } else if (command == "deanon") {
      std::size_t anonId = 0;
      std::size_t namedId = 0;
      if (parseNumber(nextWord(line, position), anonId) && parseNumber(nextWord(line, position), namedId)) {
        doDeanon(out, data, anonId, namedId);
      } else {
        printInvalid(out);
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
