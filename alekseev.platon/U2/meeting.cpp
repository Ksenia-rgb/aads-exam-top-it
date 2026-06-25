#include "meeting.hpp"

#include <istream>
#include <string>

#include <text_utils.hpp>

void alekseev::initMeetingArray(MeetingArray& meetings)
{
  initArray(meetings);
}

void alekseev::destroyMeetingArray(MeetingArray& meetings)
{
  destroyArray(meetings);
}

void alekseev::pushMeeting(MeetingArray& meetings, const Meeting& meeting)
{
  pushBack(meetings, meeting);
}

bool alekseev::parseMeetingLine(const std::string& line, Meeting& meeting)
{
  size_t position = 0;
  position = skipSpaces(line, position);
  if (position == line.size() || !parseSizeT(line, position, meeting.first))
  {
    return false;
  }

  size_t secondBegin = skipSpaces(line, position);
  if (secondBegin == position ||
      !parseSizeT(line, secondBegin, meeting.second))
  {
    return false;
  }
  position = secondBegin;

  size_t timeBegin = skipSpaces(line, position);
  if (timeBegin == position || !parseSizeT(line, timeBegin, meeting.time))
  {
    return false;
  }
  position = skipSpaces(line, timeBegin);
  return position == line.size();
}

bool alekseev::readMeetings(
    std::istream& input,
    MeetingArray& meetings,
    PersonArray& persons)
{
  std::string line;
  while (std::getline(input, line))
  {
    Meeting meeting = {0, 0, 0};
    if (!parseMeetingLine(line, meeting))
    {
      return false;
    }
    ensurePersonExists(persons, meeting.first);
    ensurePersonExists(persons, meeting.second);
    if (meeting.first != meeting.second)
    {
      pushMeeting(meetings, meeting);
    }
  }
  return input.eof();
}

size_t alekseev::findPersonIndex(const PersonArray& persons, size_t id)
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

bool alekseev::hasPersonInfo(const Person& person)
{
  return !person.info.empty();
}

void alekseev::ensurePersonExists(PersonArray& persons, size_t id)
{
  if (findPersonIndex(persons, id) != persons.size)
  {
    return;
  }
  const Person person = {id, std::string()};
  pushPerson(persons, person);
}
