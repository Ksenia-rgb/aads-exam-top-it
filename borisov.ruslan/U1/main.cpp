#include <iostream>
#include <fstream>
#include "args.hpp"
#include "person.hpp"

int main(int argc, char **argv)
{
  const borisov::Args args = borisov::parseArgs(argc, argv);
  if (!args.valid_)
  {
    return 1;
  }
  std::ifstream inFstream;
  std::ofstream outFstream;
  if (args.inSet_)
  {
    inFstream.open(args.inFile_);
    if (!inFstream.is_open())
    {
      return 2;
    }
  }
  if (args.outSet_)
  {
    outFstream.open(args.outFile_);
    if (!outFstream.is_open())
    {
      return 2;
    }
  }
  std::istream &in = args.inSet_ ? static_cast< std::istream & >(inFstream) : std::cin;
  std::ostream &out = args.outSet_ ? static_cast< std::ostream & >(outFstream) : std::cout;
  size_t count = 0;
  size_t skipped = 0;
  borisov::PersonNode * const head = borisov::readPersons(in, count, skipped);
  borisov::writePersons(out, head);
  borisov::freePersons(head);
  std::cerr << count << " " << skipped << "\n";
  return 0;
}
