#include "person_io.hpp"

#include <cstring>
#include <fstream>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>

namespace alekseev
{
  bool isLineSpace(char value)
  {
    return value == ' ' || value == '\t' || value == '\r' || value == '\v' ||
        value == '\f';
  }
}

bool alekseev::parseProgramOptions(int argc, char** argv, ProgramOptions& options)
{
  options.inputName = nullptr;
  options.outputName = nullptr;
  options.hasInput = false;
  options.hasOutput = false;

  if (argc < 1 || argc > 3)
  {
    return false;
  }

  for (int i = 1; i < argc; ++i)
  {
    const char* const argument = argv[i];
    if (argument == nullptr)
    {
      return false;
    }
    if (std::strncmp(argument, "in:", 3) == 0)
    {
      if (options.hasInput || argument[3] == '\0')
      {
        return false;
      }
      options.inputName = argument + 3;
      options.hasInput = true;
    }
    else if (std::strncmp(argument, "out:", 4) == 0)
    {
      if (options.hasOutput || argument[4] == '\0')
      {
        return false;
      }
      options.outputName = argument + 4;
      options.hasOutput = true;
    }
    else
    {
      return false;
    }
  }
  return true;
}

bool alekseev::parsePersonLine(const std::string& line, Person& person)
{
  size_t position = 0;
  size_t id = 0;
  const size_t maxId = std::numeric_limits< size_t >::max();
  while (position < line.size() && line[position] >= '0' && line[position] <= '9')
  {
    const size_t digit = static_cast< size_t >(line[position] - '0');
    if (id > (maxId - digit) / 10)
    {
      return false;
    }
    id = id * 10 + digit;
    ++position;
  }
  if (position == 0)
  {
    return false;
  }

  while (position < line.size() && isLineSpace(line[position]))
  {
    ++position;
  }
  size_t end = line.size();
  while (end > position && isLineSpace(line[end - 1]))
  {
    --end;
  }
  if (position == end)
  {
    return false;
  }

  person.id = id;
  person.info.assign(line, position, end - position);
  return true;
}

void alekseev::readPersons(
    std::istream& input,
    PersonArray& persons,
    size_t& successCount,
    size_t& ignoredCount)
{
  successCount = 0;
  ignoredCount = 0;
  std::string line;
  while (std::getline(input, line))
  {
    Person person = {0, std::string()};
    if (!parsePersonLine(line, person) || containsPersonId(persons, person.id))
    {
      ++ignoredCount;
      continue;
    }
    pushPerson(persons, person);
    ++successCount;
  }
  if (!input.eof())
  {
    throw std::runtime_error("input failure");
  }
}

void alekseev::writePersons(std::ostream& output, const PersonArray& persons)
{
  for (size_t i = 0; i < persons.size; ++i)
  {
    output << persons.data[i].id << ' ' << persons.data[i].info << '\n';
  }
  if (!output)
  {
    throw std::runtime_error("output failure");
  }
}

int alekseev::runU1(
    int argc,
    char** argv,
    std::istream& input,
    std::ostream& output,
    std::ostream& error)
{
  ProgramOptions options = {nullptr, nullptr, false, false};
  if (!parseProgramOptions(argc, argv, options))
  {
    error << "invalid arguments\n";
    return 1;
  }

  PersonArray persons = {nullptr, 0, 0};
  initPersonArray(persons);
  try
  {
    std::ifstream inputFile;
    std::istream* inputSource = &input;
    if (options.hasInput)
    {
      inputFile.open(options.inputName);
      if (!inputFile)
      {
        throw std::runtime_error("cannot open input");
      }
      inputSource = &inputFile;
    }

    size_t successCount = 0;
    size_t ignoredCount = 0;
    readPersons(*inputSource, persons, successCount, ignoredCount);
    if (inputFile.is_open())
    {
      inputFile.close();
    }

    std::ofstream outputFile;
    std::ostream* outputTarget = &output;
    if (options.hasOutput)
    {
      outputFile.open(options.outputName);
      if (!outputFile)
      {
        throw std::runtime_error("cannot open output");
      }
      outputTarget = &outputFile;
    }

    writePersons(*outputTarget, persons);
    error << successCount << ' ' << ignoredCount << '\n';
    if (!error)
    {
      throw std::runtime_error("error output failure");
    }
  }
  catch (const std::exception&)
  {
    destroyPersonArray(persons);
    error << "file or internal error\n";
    return 2;
  }
  catch (...)
  {
    destroyPersonArray(persons);
    error << "internal error\n";
    return 2;
  }

  destroyPersonArray(persons);
  return 0;
}
