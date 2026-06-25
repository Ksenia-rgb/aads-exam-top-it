#include <fstream>
#include <iostream>
#include <string>
#include "list.hpp"
#include "person.hpp"
namespace
{
struct Options
{
  std::string inputFile;
  std::string outputFile;
  bool hasInput;
  bool hasOutput;
};
bool parseArgs(int argc, char * argv[], Options & options)
{
  options.hasInput = false;
  options.hasOutput = false;
  if (argc > 3)
  {
    return false;
  }
  const std::string inPrefix = "in:";
  const std::string outPrefix = "out:";
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg = argv[i];
    if (arg.compare(0, inPrefix.size(), inPrefix) == 0)
    {
      if (options.hasInput)
      {
        return false;
      }
      const std::string name = arg.substr(inPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.inputFile = name;
      options.hasInput = true;
    }
    else if (arg.compare(0, outPrefix.size(), outPrefix) == 0)
    {
      if (options.hasOutput)
      {
        return false;
      }
      const std::string name = arg.substr(outPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.outputFile = name;
      options.hasOutput = true;
    }
    else
    {
      return false;
    }
  }
  return true;
}
bool hasId(const musorin::List< musorin::Person > & records, std::size_t id)
{
  for (const musorin::detail::Node< musorin::Person > * node = records.head;
    node != nullptr; node = node->next)
  {
    if (node->value.id == id)
    {
      return true;
    }
  }
  return false;
}
void readRecords(std::istream & in, musorin::List< musorin::Person > & records,
  std::size_t & accepted, std::size_t & ignored)
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
      ++ignored;
      continue;
    }
    if (hasId(records, person.id))
    {
      ++ignored;
      continue;
    }
    musorin::pushBack(records, person);
    ++accepted;
  }
}
void writeRecords(std::ostream & out, const musorin::List< musorin::Person > & records)
{
  for (const musorin::detail::Node< musorin::Person > * node = records.head;
    node != nullptr; node = node->next)
  {
    out << node->value.id << ' ' << node->value.info << '\n';
  }
}
}
int main(int argc, char * argv[])
{
  Options options{"", "", false, false};
  if (!parseArgs(argc, argv, options))
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  musorin::List< musorin::Person > records;
  musorin::initList(records);
  std::size_t accepted = 0;
  std::size_t ignored = 0;
  if (options.hasInput)
  {
    std::ifstream input(options.inputFile);
    if (!input.is_open())
    {
      std::cerr << "Cannot open input file\n";
      musorin::clear(records);
      return 2;
    }
    readRecords(input, records, accepted, ignored);
  }
  else
  {
    readRecords(std::cin, records, accepted, ignored);
  }
  if (options.hasOutput)
  {
    std::ofstream output(options.outputFile);
    if (!output.is_open())
    {
      std::cerr << "Cannot open output file\n";
      musorin::clear(records);
      return 2;
    }
    writeRecords(output, records);
  }
  else
  {
    writeRecords(std::cout, records);
  }
  
  if (accepted != 0 || ignored != 0)
  {
    std::cerr << accepted << ' ' << ignored << '\n';
  }
  musorin::clear(records);
  return 0;
}
