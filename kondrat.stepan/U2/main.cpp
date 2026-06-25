#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <utils.hpp>

namespace kondrat
{
  struct Person
  {
    size_t id;
    std::string info;
    bool described;
  };

  struct Meeting
  {
    size_t first;
    size_t second;
    size_t time;
  };

  template< class T >
  struct Storage
  {
    T * data;
    size_t size;
    size_t capacity;
  };

  using PersonStorage = Storage< Person >;
  using MeetingStorage = Storage< Meeting >;

  struct ProgramArgs
  {
    const char * input;
    const char * data;
  };

  bool parseArgs(int argc, char ** argv, ProgramArgs & args);
  template< class T >
  void initStorage(Storage< T > & storage);
  template< class T >
  void destroyStorage(Storage< T > & storage);
  template< class T >
  void reserve(Storage< T > & storage, size_t capacity);
  template< class T >
  void pushBack(Storage< T > & storage, const T & value);
  bool isBlank(const std::string & line);
  bool parsePerson(const std::string & line, Person & person);
  Person * findPerson(PersonStorage & storage, size_t id);
  bool containsPerson(const PersonStorage & storage, size_t id);
  void ensureAnonPerson(PersonStorage & storage, size_t id);
  void readPersons(std::istream & input, PersonStorage & storage);
  bool parseMeeting(const std::string & line, Meeting & meeting);
  bool readMeetings(std::istream & input, MeetingStorage & meetings, PersonStorage & persons);
}

bool kondrat::parseArgs(int argc, char ** argv, ProgramArgs & args)
{
  args.input = nullptr;
  args.data = nullptr;
  if (argc < 2 || argc > 3)
  {
    return false;
  }

  for (int i = 1; i < argc; ++i)
  {
    if (startsWith(argv[i], "in:"))
    {
      if (args.input != nullptr || argv[i][3] == '\0')
      {
        return false;
      }
      args.input = argv[i] + 3;
    }
    else if (startsWith(argv[i], "data:"))
    {
      if (args.data != nullptr || argv[i][5] == '\0')
      {
        return false;
      }
      args.data = argv[i] + 5;
    }
    else
    {
      return false;
    }
  }

  return args.data != nullptr;
}

template< class T >
void kondrat::initStorage(Storage< T > & storage)
{
  storage.data = nullptr;
  storage.size = 0;
  storage.capacity = 0;
}

template< class T >
void kondrat::destroyStorage(Storage< T > & storage)
{
  delete[] storage.data;
  initStorage(storage);
}

template< class T >
void kondrat::reserve(Storage< T > & storage, size_t capacity)
{
  if (capacity <= storage.capacity)
  {
    return;
  }

  T * newData = new T[capacity];
  try
  {
    for (size_t i = 0; i < storage.size; ++i)
    {
      newData[i] = storage.data[i];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }

  delete[] storage.data;
  storage.data = newData;
  storage.capacity = capacity;
}

template< class T >
void kondrat::pushBack(Storage< T > & storage, const T & value)
{
  if (storage.size == storage.capacity)
  {
    reserve(storage, nextCapacity(storage.capacity));
  }

  storage.data[storage.size] = value;
  ++storage.size;
}

bool kondrat::isBlank(const std::string & line)
{
  for (size_t i = 0; i < line.size(); ++i)
  {
    if (!isSpace(line[i]))
    {
      return false;
    }
  }
  return true;
}

bool kondrat::parsePerson(const std::string & line, Person & person)
{
  size_t first = 0;
  while (first < line.size() && isSpace(line[first]))
  {
    ++first;
  }

  size_t id = 0;
  if (!readSizeT(line, first, id))
  {
    return false;
  }

  size_t afterId = first;
  if (afterId < line.size() && !isSpace(line[afterId]))
  {
    return false;
  }
  while (afterId < line.size() && isSpace(line[afterId]))
  {
    ++afterId;
  }
  if (afterId == line.size())
  {
    return false;
  }

  person.id = id;
  person.info = line.substr(afterId);
  person.described = true;
  return true;
}

bool kondrat::containsPerson(const PersonStorage & storage, size_t id)
{
  for (size_t i = 0; i < storage.size; ++i)
  {
    if (storage.data[i].id == id)
    {
      return true;
    }
  }
  return false;
}

kondrat::Person * kondrat::findPerson(PersonStorage & storage, size_t id)
{
  for (size_t i = 0; i < storage.size; ++i)
  {
    if (storage.data[i].id == id)
    {
      return storage.data + i;
    }
  }
  return nullptr;
}

void kondrat::ensureAnonPerson(PersonStorage & storage, size_t id)
{
  if (findPerson(storage, id) != nullptr)
  {
    return;
  }

  Person person = {};
  person.id = id;
  person.info = "";
  person.described = false;
  pushBack(storage, person);
}

void kondrat::readPersons(std::istream & input, PersonStorage & storage)
{
  std::string line;
  while (std::getline(input, line))
  {
    if (isBlank(line))
    {
      continue;
    }

    Person person = {};
    if (!parsePerson(line, person) || containsPerson(storage, person.id))
    {
      continue;
    }
    pushBack(storage, person);
  }
}

bool kondrat::parseMeeting(const std::string & line, Meeting & meeting)
{
  size_t pos = 0;
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }

  size_t first = 0;
  if (!readSizeT(line, pos, first) || pos == line.size() || !isSpace(line[pos]))
  {
    return false;
  }
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }

  size_t second = 0;
  if (!readSizeT(line, pos, second) || pos == line.size() || !isSpace(line[pos]))
  {
    return false;
  }
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }

  size_t time = 0;
  if (!readSizeT(line, pos, time))
  {
    return false;
  }
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }
  if (pos != line.size())
  {
    return false;
  }

  meeting.first = first;
  meeting.second = second;
  meeting.time = time;
  return true;
}

bool kondrat::readMeetings(std::istream & input, MeetingStorage & meetings, PersonStorage & persons)
{
  std::string line;
  while (std::getline(input, line))
  {
    if (isBlank(line))
    {
      continue;
    }

    Meeting meeting = {};
    if (!parseMeeting(line, meeting))
    {
      return false;
    }
    if (meeting.first == meeting.second)
    {
      continue;
    }
    ensureAnonPerson(persons, meeting.first);
    ensureAnonPerson(persons, meeting.second);
    pushBack(meetings, meeting);
  }
  return true;
}

int main(int argc, char ** argv)
{
  kondrat::ProgramArgs args = {};
  if (!kondrat::parseArgs(argc, argv, args))
  {
    std::cerr << "<INVALID ARGUMENTS>\n";
    return 1;
  }

  std::ifstream personFile;
  std::istream * personInput = nullptr;
  if (args.input != nullptr)
  {
    personFile.open(args.input);
    if (!personFile)
    {
      std::cerr << "<FILE ERROR>\n";
      return 2;
    }
    personInput = &personFile;
  }

  std::ifstream meetingFile(args.data);
  if (!meetingFile)
  {
    std::cerr << "<FILE ERROR>\n";
    return 2;
  }

  kondrat::PersonStorage persons = {};
  kondrat::MeetingStorage meetings = {};
  kondrat::initStorage(persons);
  kondrat::initStorage(meetings);
  try
  {
    if (personInput != nullptr)
    {
      kondrat::readPersons(*personInput, persons);
    }
    if (!kondrat::readMeetings(meetingFile, meetings, persons))
    {
      kondrat::destroyStorage(meetings);
      kondrat::destroyStorage(persons);
      std::cerr << "<INVALID DATA>\n";
      return 3;
    }
  }
  catch (...)
  {
    kondrat::destroyStorage(meetings);
    kondrat::destroyStorage(persons);
    throw;
  }

  kondrat::destroyStorage(meetings);
  kondrat::destroyStorage(persons);
  return 0;
}
