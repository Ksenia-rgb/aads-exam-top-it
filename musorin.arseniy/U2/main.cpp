		#include <fstream>
#include <iostream>
#include <string>
#include "list.hpp"
#include "person.hpp"
#include "meet.hpp"
namespace
{
struct Options
{
  std::string dataFile;
  std::string personsFile;
  bool hasPersons;
};
bool parseArgs(int argc, char * argv[], Options & options)
{
  options.hasPersons = false;
  bool hasData = false;
  if (argc < 2 || argc > 3)
  {
    return false;
  }
  const std::string dataPrefix = "data:";
  const std::string inPrefix = "in:";
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg = argv[i];
    if (arg.compare(0, dataPrefix.size(), dataPrefix) == 0)
    {
      if (hasData)
      {
        return false;
      }
      const std::string name = arg.substr(dataPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.dataFile = name;
      hasData = true;
    }
    else if (arg.compare(0, inPrefix.size(), inPrefix) == 0)
    {
      if (options.hasPersons)
      {
        return false;
      }
      const std::string name = arg.substr(inPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.personsFile = name;
      options.hasPersons = true;
    }
    else
    {
      return false;
    }
  }
  return hasData;
}
bool hasPerson(const musorin::List< musorin::Person > & persons, std::size_t id)
{
  for (const musorin::detail::Node< musorin::Person > * node = persons.head;
    node != nullptr; node = node->next)
  {
    if (node->value.id == id)
    {
      return true;
    }
  }
  return false;
}
void ensurePerson(musorin::List< musorin::Person > & persons, std::size_t id)
{
  if (hasPerson(persons, id))
  {
    return;
  }
  musorin::Person anon{id, ""};
  musorin::pushBack(persons, anon);
}
void loadPersons(std::istream & in, musorin::List< musorin::Person > & persons)
{
  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty())
    {
      continue;
    }
    musorin::Person person{0, ""};
    if (!musorin::parseLine(line, person))
    {
      continue;
    }
    if (hasPerson(persons, person.id))
    {
      continue;
    }
    musorin::pushBack(persons, person);
  }
}
bool loadMeets(std::istream & in, musorin::List< musorin::Person > & persons,
  musorin::List< musorin::Meet > & meets)
{
  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty())
    {
      continue;
    }
    musorin::Meet meet{0, 0, 0};
    if (!musorin::parseMeetLine(line, meet))
    {
      return false;
    }
    if (meet.from == meet.to)
    {
      continue;
    }
    ensurePerson(persons, meet.from);
    ensurePerson(persons, meet.to);
    musorin::pushBack(meets, meet);
  }
  return true;
}
bool isSpaceChar(char ch)
{
  return ch == ' ' || ch == '\t';
}
bool isDigitChar(char ch)
{
  return ch >= '0' && ch <= '9';
}
void splitLine(const std::string & line, musorin::List< std::string > & tokens)
{
  std::size_t pos = 0;
  while (pos < line.size())
  {
    while (pos < line.size() && isSpaceChar(line[pos]))
    {
      ++pos;
    }
    if (pos == line.size())
    {
      break;
    }
    const std::size_t start = pos;
    while (pos < line.size() && !isSpaceChar(line[pos]))
    {
      ++pos;
    }
    musorin::pushBack(tokens, line.substr(start, pos - start));
  }
}
bool toId(const std::string & token, std::size_t & value)
{
  if (token.empty())
  {
    return false;
  }
  std::size_t result = 0;
  for (std::size_t i = 0; i < token.size(); ++i)
  {
    if (!isDigitChar(token[i]))
    {
      return false;
    }
    const std::size_t digit = static_cast< std::size_t >(token[i] - '0');
    result = result * 10 + digit;
  }
  value = result;
  return true;
}
void printInvalid(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}
bool extractCommand(const std::string & line, std::string & command, std::string & rest)
{
  std::size_t pos = 0;
  while (pos < line.size() && isSpaceChar(line[pos]))
  {
    ++pos;
  }
  if (pos == line.size())
  {
    return false;
  }
  const std::size_t start = pos;
  while (pos < line.size() && !isSpaceChar(line[pos]))
  {
    ++pos;
  }
  command = line.substr(start, pos - start);
  while (pos < line.size() && isSpaceChar(line[pos]))
  {
    ++pos;
  }
  rest = line.substr(pos);
  return true;
}
musorin::Person * findPerson(musorin::List< musorin::Person > & persons, std::size_t id)
{
  for (musorin::detail::Node< musorin::Person > * node = persons.head;
    node != nullptr; node = node->next)
  {
    if (node->value.id == id)
    {
      return &node->value;
    }
  }
  return nullptr;
}
template< class T, class Compare >
void sortList(musorin::List< T > & list, Compare cmp)
{
  if (list.size < 2)
  {
    return;
  }
  musorin::List< T > sorted;
  musorin::initList(sorted);
  musorin::detail::Node< T > * current = list.head;
  while (current != nullptr)
  {
    musorin::detail::Node< T > * next = current->next;
    musorin::detail::Node< T > * prev = nullptr;
    musorin::detail::Node< T > * scan = sorted.head;
    while (scan != nullptr && cmp(scan->value, current->value))
    {
      prev = scan;
      scan = scan->next;
    }
    current->next = scan;
    if (prev == nullptr)
    {
      sorted.head = current;
    }
    else
    {
      prev->next = current;
    }
    if (scan == nullptr)
    {
      sorted.tail = current;
    }
    ++sorted.size;
    current = next;
  }
  list.head = sorted.head;
  list.tail = sorted.tail;
  list.size = sorted.size;
}
bool lessSizeT(const std::size_t & a, const std::size_t & b)
{
  return a < b;
}
void cmdAnons(const musorin::List< musorin::Person > & persons, std::ostream & out)
{
  musorin::List< std::size_t > ids;
  musorin::initList(ids);
  for (const musorin::detail::Node< musorin::Person > * node = persons.head;
    node != nullptr; node = node->next)
  {
    if (node->value.info.empty())
    {
      musorin::pushBack(ids, node->value.id);
    }
  }
  sortList(ids, lessSizeT);
  for (const musorin::detail::Node< std::size_t > * node = ids.head;
    node != nullptr; node = node->next)
  {
    out << node->value << '\n';
  }
  musorin::clear(ids);
}
void cmdDesc(musorin::List< musorin::Person > & persons,
  const musorin::List< std::string > & args, std::ostream & out)
{
  if (args.size != 1)
  {
    printInvalid(out);
    return;
  }
  std::size_t id = 0;
  if (!toId(args.head->value, id))
  {
    printInvalid(out);
    return;
  }
  musorin::Person * person = findPerson(persons, id);
  if (person == nullptr)
  {
    printInvalid(out);
    return;
  }
  if (person->info.empty())
  {
    out << "<ANON>\n";
  }
  else
  {
    out << person->info << '\n';
  }
}
struct Partner
{
  std::size_t id;
  std::size_t duration;
};
bool lessPartner(const Partner & a, const Partner & b)
{
  if (a.id != b.id)
  {
    return a.id < b.id;
  }
  return a.duration < b.duration;
}
void collectMeets(const musorin::List< musorin::Meet > & meets, std::size_t personId,
  musorin::List< Partner > & result)
{
  for (const musorin::detail::Node< musorin::Meet > * node = meets.head;
    node != nullptr; node = node->next)
  {
    const musorin::Meet & meet = node->value;
    if (meet.from == personId)
    {
      Partner partner{meet.to, meet.duration};
      musorin::pushBack(result, partner);
    }
    else if (meet.to == personId)
    {
      Partner partner{meet.from, meet.duration};
      musorin::pushBack(result, partner);
    }
  }
}
void printPartners(const musorin::List< Partner > & partners, std::ostream & out)
{
  for (const musorin::detail::Node< Partner > * node = partners.head;
    node != nullptr; node = node->next)
  {
    out << node->value.id << ' ' << node->value.duration << '\n';
  }
}
void cmdMeets(const musorin::List< musorin::Person > & persons,
  const musorin::List< musorin::Meet > & meets,
  const musorin::List< std::string > & args, std::ostream & out)
{
  if (args.size != 1)
  {
    printInvalid(out);
    return;
  }
  std::size_t id = 0;
  if (!toId(args.head->value, id))
  {
    printInvalid(out);
    return;
  }
  if (!hasPerson(persons, id))
  {
    printInvalid(out);
    return;
  }
  musorin::List< Partner > collected;
  musorin::initList(collected);
  collectMeets(meets, id, collected);
  sortList(collected, lessPartner);
  printPartners(collected, out);
  musorin::clear(collected);
}
void cmdFilterByDuration(const musorin::List< musorin::Person > & persons,
  const musorin::List< musorin::Meet > & meets,
  const musorin::List< std::string > & args, std::ostream & out, bool greater)
{
  if (args.size != 2)
  {
    printInvalid(out);
    return;
  }
  std::size_t threshold = 0;
  std::size_t id = 0;
  if (!toId(args.head->value, threshold) || !toId(args.head->next->value, id))
  {
    printInvalid(out);
    return;
  }
  if (!hasPerson(persons, id))
  {
    printInvalid(out);
    return;
  }
  musorin::List< Partner > collected;
  musorin::initList(collected);
  collectMeets(meets, id, collected);
  musorin::List< Partner > filtered;
  musorin::initList(filtered);
  for (const musorin::detail::Node< Partner > * node = collected.head;
    node != nullptr; node = node->next)
  {
    const bool keep = greater ? (node->value.duration > threshold)
      : (node->value.duration < threshold);
    if (keep)
    {
      musorin::pushBack(filtered, node->value);
    }
  }
  sortList(filtered, lessPartner);
  printPartners(filtered, out);
  musorin::clear(collected);
  musorin::clear(filtered);
}
bool listHasId(const musorin::List< std::size_t > & ids, std::size_t id)
{
  for (const musorin::detail::Node< std::size_t > * node = ids.head;
    node != nullptr; node = node->next)
  {
    if (node->value == id)
    {
      return true;
    }
  }
  return false;
}
void cmdCommons(const musorin::List< musorin::Person > & persons,
  const musorin::List< musorin::Meet > & meets,
  const musorin::List< std::string > & args, std::ostream & out)
{
  if (args.size != 2)
  {
    printInvalid(out);
    return;
  }
  std::size_t id1 = 0;
  std::size_t id2 = 0;
  if (!toId(args.head->value, id1) || !toId(args.head->next->value, id2))
  {
    printInvalid(out);
    return;
  }
  if (!hasPerson(persons, id1) || !hasPerson(persons, id2))
  {
    printInvalid(out);
    return;
  }
  musorin::List< Partner > first;
  musorin::initList(first);
  collectMeets(meets, id1, first);
  musorin::List< Partner > second;
  musorin::initList(second);
  collectMeets(meets, id2, second);
  musorin::List< std::size_t > commons;
  musorin::initList(commons);
  for (const musorin::detail::Node< Partner > * a = first.head; a != nullptr; a = a->next)
  {
    if (listHasId(commons, a->value.id))
    {
      continue;
    }
    for (const musorin::detail::Node< Partner > * b = second.head; b != nullptr; b = b->next)
    {
      if (a->value.id == b->value.id)
      {
        musorin::pushBack(commons, a->value.id);
        break;
      }
    }
  }
  sortList(commons, lessSizeT);
  for (const musorin::detail::Node< std::size_t > * node = commons.head;
    node != nullptr; node = node->next)
  {
    out << node->value << '\n';
  }
  musorin::clear(first);
  musorin::clear(second);
  musorin::clear(commons);
}
void rewriteMeetIds(musorin::List< musorin::Meet > & meets, std::size_t fromId,
  std::size_t toId)
{
  for (musorin::detail::Node< musorin::Meet > * node = meets.head;
    node != nullptr; node = node->next)
  {
    if (node->value.from == fromId)
    {
      node->value.from = toId;
    }
    if (node->value.to == fromId)
    {
      node->value.to = toId;
    }
  }
}
bool isSelfMeet(const musorin::Meet & meet)
{
  return meet.from == meet.to;
}
bool isPersonWithId(std::size_t id, const musorin::Person & person)
{
  return person.id == id;
}
void cmdDeanon(musorin::List< musorin::Person > & persons,
  musorin::List< musorin::Meet > & meets,
  const musorin::List< std::string > & args, std::ostream & out)
{
  if (args.size != 2)
  {
    printInvalid(out);
    return;
  }
  std::size_t anonId = 0;
  std::size_t targetId = 0;
  if (!toId(args.head->value, anonId) || !toId(args.head->next->value, targetId))
  {
    printInvalid(out);
    return;
  }
  if (anonId == targetId)
  {
    printInvalid(out);
    return;
  }
  musorin::Person * anonPerson = findPerson(persons, anonId);
  musorin::Person * targetPerson = findPerson(persons, targetId);
  if (anonPerson == nullptr || targetPerson == nullptr)
  {
    printInvalid(out);
    return;
  }
  if (!anonPerson->info.empty())
  {
    printInvalid(out);
    return;
  }
  if (targetPerson->info.empty())
  {
    printInvalid(out);
    return;
  }
  rewriteMeetIds(meets, anonId, targetId);
  musorin::removeIf(meets, isSelfMeet);
  const std::size_t idToRemove = anonId;
  musorin::removeIf(persons, [idToRemove](const musorin::Person & person) {
    return person.id == idToRemove;
  });
}
bool parseRedescPayload(const std::string & line, std::size_t & id,
  std::string & description)
{
  std::size_t pos = 0;
  while (pos < line.size() && isSpaceChar(line[pos]))
  {
    ++pos;
  }
  if (pos == line.size() || !isDigitChar(line[pos]))
  {
    return false;
  }
  std::size_t value = 0;
  while (pos < line.size() && isDigitChar(line[pos]))
  {
    const std::size_t digit = static_cast< std::size_t >(line[pos] - '0');
    value = value * 10 + digit;
    ++pos;
  }
  while (pos < line.size() && isSpaceChar(line[pos]))
  {
    ++pos;
  }
  if (pos == line.size() || line[pos] != '"')
  {
    return false;
  }
  ++pos;
  const std::size_t start = pos;
  while (pos < line.size() && line[pos] != '"')
  {
    ++pos;
  }
  if (pos == line.size())
  {
    return false;
  }
  const std::size_t end = pos;
  ++pos;
  while (pos < line.size() && isSpaceChar(line[pos]))
  {
    ++pos;
  }
  if (pos != line.size())
  {
    return false;
  }
  if (end == start)
  {
    return false;
  }
  id = value;
  description = line.substr(start, end - start);
  return true;
}
void cmdRedesc(musorin::List< musorin::Person > & persons, const std::string & payload,
  std::ostream & out)
{
  std::size_t id = 0;
  std::string description;
  if (!parseRedescPayload(payload, id, description))
  {
    printInvalid(out);
    return;
  }
  musorin::Person * person = findPerson(persons, id);
  if (person == nullptr)
  {
    printInvalid(out);
    return;
  }
  person->info = description;
}
void cmdOutPersons(const musorin::List< musorin::Person > & persons,
  const musorin::List< std::string > & args, std::ostream & out)
{
  if (args.size != 1)
  {
    printInvalid(out);
    return;
  }
  std::ofstream file(args.head->value);
  if (!file.is_open())
  {
    printInvalid(out);
    return;
  }
  for (const musorin::detail::Node< musorin::Person > * node = persons.head;
    node != nullptr; node = node->next)
  {
    if (!node->value.info.empty())
    {
      file << node->value.id << ' ' << node->value.info << '\n';
    }
  }
}
void runCommands(musorin::List< musorin::Person > & persons,
  const musorin::List< musorin::Meet > & meets,
  std::istream & in, std::ostream & out)
{
  std::string line;
  while (std::getline(in, line))
  {
    std::string command;
    std::string rest;
    if (!extractCommand(line, command, rest))
    {
      continue;
    }
    musorin::List< std::string > args;
    musorin::initList(args);
    splitLine(rest, args);
    if (command == "anons")
    {
      if (args.size != 0)
      {
        printInvalid(out);
      }
      else
      {
        cmdAnons(persons, out);
      }
    }
    else if (command == "desc")
    {
      cmdDesc(persons, args, out);
    }
    else if (command == "redesc")
    {
      cmdRedesc(persons, rest, out);
    }
    else if (command == "out-persons")
    {
      cmdOutPersons(persons, args, out);
    }
    else if (command == "meets")
    {
      cmdMeets(persons, meets, args, out);
    }
    else if (command == "less")
    {
      cmdFilterByDuration(persons, meets, args, out, false);
    }
    else if (command == "greater")
    {
      cmdFilterByDuration(persons, meets, args, out, true);
    }
    else if (command == "commons")
    {
      cmdCommons(persons, meets, args, out);
    }
    else
    {
      printInvalid(out);
    }
    musorin::clear(args);
  }
}
}
int main(int argc, char * argv[])
{
  Options options{"", "", false};
  if (!parseArgs(argc, argv, options))
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  musorin::List< musorin::Person > persons;
  musorin::initList(persons);
  musorin::List< musorin::Meet > meets;
  musorin::initList(meets);
  if (options.hasPersons)
  {
    std::ifstream personsStream(options.personsFile);
    if (!personsStream.is_open())
    {
      std::cerr << "Cannot open persons file\n";
      musorin::clear(persons);
      musorin::clear(meets);
      return 2;
    }
    loadPersons(personsStream, persons);
  }
  std::ifstream dataStream(options.dataFile);
  if (!dataStream.is_open())
  {
    std::cerr << "Cannot open data file\n";
    musorin::clear(persons);
    musorin::clear(meets);
    return 2;
  }
  if (!loadMeets(dataStream, persons, meets))
  {
    std::cerr << "Invalid meets data\n";
    musorin::clear(persons);
    musorin::clear(meets);
    return 3;
  }
  runCommands(persons, meets, std::cin, std::cout);
  musorin::clear(persons);
  musorin::clear(meets);
  return 0;
}
