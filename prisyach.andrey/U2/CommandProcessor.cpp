#include "CommandProcessor.h"
#include "DataStore.h"
#include "StringTrim.h"
#include "UnsignedParser.h"
#include <cstdio>
#include <cstring>
#include <iterator>
#include <vector>

namespace {
bool parseUnsignedToken(const char* begin,
                        const char* end,
                        std::size_t& value,
                        const char*& next) {
  const char* current = skipWhitespace(begin, end);
  if (current >= end) {
    return false;
  }
  if (!parseUnsignedSizeT(current, end, value, next)) {
    return false;
  }
  return true;
}

bool parseFilename(const char* begin,
                   const char* end,
                   std::string& filename) {
  const char* current = skipWhitespace(begin, end);
  if (current >= end) {
    return false;
  }
  const char* next = current;
  while (next < end && *next != ' ' && *next != '\t') {
    ++next;
  }
  if (current >= next) {
    return false;
  }
  filename.assign(current, next);
  current = skipWhitespace(next, end);
  return current >= end;
}

bool parseQuotedDescription(const char* begin,
                            const char* end,
                            std::string& description) {
  const char* current = skipWhitespace(begin, end);
  if (current >= end || *current != '"') {
    return false;
  }
  ++current;
  const char* start = current;
  while (current < end && *current != '"') {
    ++current;
  }
  if (current >= end || *current != '"') {
    return false;
  }
  description.assign(start, current);
  ++current;
  current = skipWhitespace(current, end);
  return current >= end;
}

void printInvalid() {
  std::printf("<INVALID COMMAND>\n");
}

void sortMeetings(std::vector<Meeting>& meetings) {
  std::sort(meetings.begin(), meetings.end(),
            [](Meeting const& a, Meeting const& b) {
              if (a.other != b.other) {
                return a.other < b.other;
              }
              return a.duration < b.duration;
            });
}

}

CommandProcessor::CommandProcessor(DataStore& dataStore)
  : dataStore_(dataStore) {
}

void CommandProcessor::processCommandLine(const std::string& line) {
  const char* begin = line.c_str();
  const char* end = begin + line.size();
  const char* current = skipWhitespace(begin, end);
  if (current >= end) {
    return;
  }
  const char* tokenEnd = current;
  while (tokenEnd < end && *tokenEnd != ' ' && *tokenEnd != '\t') {
    ++tokenEnd;
  }
  std::string command(current, tokenEnd);
  current = tokenEnd;
  if (command == "anons") {
    current = skipWhitespace(current, end);
    if (current < end) {
      printInvalid();
      return;
    }
    std::vector<std::size_t> ids;
    dataStore_.anonymousIds(ids);
    for (std::size_t id : ids) {
      std::printf("%zu\n", id);
    }
    return;
  }
  if (command == "deanon") {
    std::size_t anonId = 0;
    std::size_t descId = 0;
    if (!parseUnsignedToken(current, end, anonId, current) ||
        !parseUnsignedToken(current, end, descId, current)) {
      printInvalid();
      return;
    }
    current = skipWhitespace(current, end);
    if (current < end) {
      printInvalid();
      return;
    }
    if (!dataStore_.hasPerson(anonId) || !dataStore_.hasPerson(descId)) {
      printInvalid();
      return;
    }
    if (anonId == descId || dataStore_.hasDescription(anonId) ||
        !dataStore_.hasDescription(descId)) {
      printInvalid();
      return;
    }
    if (!dataStore_.mergeAnonymous(anonId, descId)) {
      printInvalid();
    }
    return;
  }
  if (command == "redesc") {
    std::size_t id = 0;
    const char* next = nullptr;
    if (!parseUnsignedToken(current, end, id, next)) {
      printInvalid();
      return;
    }
    std::string description;
    if (!parseQuotedDescription(next, end, description)) {
      printInvalid();
      return;
    }
    if (!dataStore_.hasPerson(id)) {
      printInvalid();
      return;
    }
    dataStore_.setDescription(id, description);
    return;
  }
  if (command == "desc") {
    std::size_t id = 0;
    if (!parseUnsignedToken(current, end, id, current)) {
      printInvalid();
      return;
    }
    current = skipWhitespace(current, end);
    if (current < end) {
      printInvalid();
      return;
    }
    if (!dataStore_.hasPerson(id)) {
      printInvalid();
      return;
    }
    if (!dataStore_.hasDescription(id)) {
      std::printf("<ANON>\n");
      return;
    }
    std::printf("%s\n", dataStore_.description(id).c_str());
    return;
  }
  if (command == "meets" || command == "less" || command == "greater") {
    std::size_t first = 0;
    std::size_t second = 0;
    if (command == "meets") {
      if (!parseUnsignedToken(current, end, first, current)) {
        printInvalid();
        return;
      }
      current = skipWhitespace(current, end);
      if (current < end) {
        printInvalid();
        return;
      }
      if (!dataStore_.hasPerson(first)) {
        printInvalid();
        return;
      }
      std::vector<Meeting> meetings;
      dataStore_.meetingPairs(first, meetings);
      sortMeetings(meetings);
      for (auto const& meeting : meetings) {
        std::printf("%zu %zu\n", meeting.other, meeting.duration);
      }
      return;
    }
    if (!parseUnsignedToken(current, end, first, current)) {
      printInvalid();
      return;
    }
    if (!parseUnsignedToken(current, end, second, current)) {
      printInvalid();
      return;
    }
    current = skipWhitespace(current, end);
    if (current < end) {
      printInvalid();
      return;
    }
    if (!dataStore_.hasPerson(second)) {
      printInvalid();
      return;
    }
    std::vector<Meeting> meetings;
    dataStore_.meetingPairs(second, meetings);
    std::vector<Meeting> filtered;
    for (auto const& meeting : meetings) {
      if (command == "less") {
        if (meeting.duration < first) {
          filtered.push_back(meeting);
        }
      } else if (meeting.duration > first) {
        filtered.push_back(meeting);
      }
    }
    sortMeetings(filtered);
    for (auto const& meeting : filtered) {
      std::printf("%zu %zu\n", meeting.other, meeting.duration);
    }
    return;
  }
  if (command == "commons") {
    std::size_t id1 = 0;
    std::size_t id2 = 0;
    if (!parseUnsignedToken(current, end, id1, current) ||
        !parseUnsignedToken(current, end, id2, current)) {
      printInvalid();
      return;
    }
    current = skipWhitespace(current, end);
    if (current < end) {
      printInvalid();
      return;
    }
    if (!dataStore_.hasPerson(id1) || !dataStore_.hasPerson(id2)) {
      printInvalid();
      return;
    }
    std::vector<std::size_t> contacts;
    dataStore_.commonContacts(id1, id2, contacts);
    for (std::size_t id : contacts) {
      std::printf("%zu\n", id);
    }
    return;
  }
  if (command == "out-persons") {
    std::string filename;
    if (!parseFilename(current, end, filename)) {
      printInvalid();
      return;
    }
    std::string error;
    if (!dataStore_.outputPersons(filename, error)) {
      printInvalid();
    }
    return;
  }
  printInvalid();
}
