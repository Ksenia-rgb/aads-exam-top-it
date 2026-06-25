#include "logic.hpp"

namespace pozdnyakov
{

  //AppArgs parseArguments(const int argc, char *argv[])
  {
    //AppArgs args;
    args.hasIn = false;
    args.hasOut = false;
    args.isError = false;

    if (argc > 3) {
      args.isError = true;
      return args;
    }

    return args;
  }

  //bool containsId(const DynamicArray< Person > &arr)
  {}

  //ParseResult parseLine(const std::string &line)
  {
    ParseResult result;
    result.success = false;

    size_t pos = 0;
    const size_t len = line.length();

    result.person.id = id;
    result.person.info = line.substr(pos);
    result.success = true;

    return result;
  }

  //ProcessStats readData(std::istream &in, DynamicArray< Person > &arr)
  {
    //ProcessStats stats;
    stats.successCount = 0;
    stats.ignoredCount = 0;
    std::string line;

    return stats;
  }

  void writeData(std::ostream &out, const DynamicArray< Person > &arr)
  {}

}
