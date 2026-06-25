#include "commands.hpp"
#include <ostream>
#include "../common/ordered-list.hpp"
#include "../common/parse.hpp"
#include "../common/person-io.hpp"

namespace
{
  struct AnonsData
  {
    shaykhraziev::U2Storage* storage;
    shaykhraziev::List< size_t >* result;
  };

  void collectAnonId(shaykhraziev::HashEntry< size_t, bool >& entry, void* data)
  {
    AnonsData* anons = static_cast< AnonsData* >(data);
    if (!shaykhraziev::contains(anons->storage->personsById, entry.key))
    {
      shaykhraziev::insertOrderedUniqueSizeT(*anons->result, entry.key);
    }
  }

  bool parseCommandPrefix(const std::string& line, const char* command, size_t& position)
  {
    if (!shaykhraziev::startsWith(line, command))
    {
      return false;
    }
    position = 0;
    while (command[position] != '\0')
    {
      ++position;
    }
    if ((position < line.size()) && (line[position] != ' ') && (line[position] != '\t'))
    {
      return false;
    }
    return true;
  }

  bool parseIdCommand(const std::string& line, const char* command, size_t& id)
  {
    size_t position = 0;
    if (!parseCommandPrefix(line, command, position))
    {
      return false;
    }
    if (!shaykhraziev::parseSizeTPrefix(line, id, position))
    {
      return false;
    }
    return shaykhraziev::skipSpaces(line, position) == line.size();
  }

  bool parseRedescCommand(const std::string& line, size_t& id, std::string& description)
  {
    size_t position = 0;
    if (!parseCommandPrefix(line, "redesc", position))
    {
      return false;
    }
    if (!shaykhraziev::parseSizeTPrefix(line, id, position))
    {
      return false;
    }
    position = shaykhraziev::skipSpaces(line, position);
    if ((position >= line.size()) || (line[position] != '"'))
    {
      return false;
    }
    ++position;
    const size_t begin = position;
    while ((position < line.size()) && (line[position] != '"'))
    {
      ++position;
    }
    if (position >= line.size())
    {
      return false;
    }
    description = line.substr(begin, position - begin);
    ++position;
    return shaykhraziev::skipSpaces(line, position) == line.size();
  }
}

bool shaykhraziev::executeAnons(U2Storage& storage, std::ostream& output)
{
  List< size_t > anons;
  initList(anons);
  AnonsData data = { &storage, &anons };
  forEachEntry(storage.knownIds, collectAnonId, &data);
  ListIterator< size_t > iterator = begin(anons);
  while (!isEnd(iterator))
  {
    output << get(iterator) << '\n';
    iterator = next(iterator);
  }
  clearList(anons);
  return true;
}

bool shaykhraziev::executeDesc(U2Storage& storage, const std::string& line, std::ostream& output)
{
  size_t id = 0;
  if (!parseIdCommand(line, "desc", id) || !contains(storage.knownIds, id))
  {
    return false;
  }
  Person* person = findPersonById(storage.personsById, id);
  if (person == nullptr)
  {
    output << "<ANON>\n";
  }
  else
  {
    output << person->info << '\n';
  }
  return true;
}

bool shaykhraziev::executeRedesc(U2Storage& storage, const std::string& line)
{
  size_t id = 0;
  std::string description;
  if (!parseRedescCommand(line, id, description) || !contains(storage.knownIds, id))
  {
    return false;
  }
  Person* person = findPersonById(storage.personsById, id);
  if (person != nullptr)
  {
    person->info = description;
    return true;
  }
  const Person newPerson = { id, description };
  return addPerson(storage.persons, storage.personsById, newPerson);
}
