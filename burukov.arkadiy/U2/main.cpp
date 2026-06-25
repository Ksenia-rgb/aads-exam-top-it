#include <fstream>
#include <iostream>

#include <args.hpp>

#include "commands.hpp"
#include "loader.hpp"
#include "model.hpp"

namespace
{

  int run(const burukov::DataArgs& args, burukov::Graph& graph)
  {
    if (args.hasIn)
    {
      std::ifstream personsStream(args.inFile.c_str());
      if (!personsStream.is_open())
      {
        std::cerr << "Cannot open input file" << "\n";
        return 2;
      }
      burukov::loadPersons(personsStream, graph);
    }
    std::ifstream dataStream(args.dataFile.c_str());
    if (!dataStream.is_open())
    {
      std::cerr << "Cannot open data file" << "\n";
      return 2;
    }
    if (!burukov::loadMeetings(dataStream, graph))
    {
      std::cerr << "Invalid meetings data" << "\n";
      return 3;
    }
    burukov::runCommands(std::cin, std::cout, graph);
    return 0;
  }

}

int main(int argc, char** argv)
{
  burukov::DataArgs args = burukov::parseDataArgs(argc, argv);
  if (!args.valid)
  {
    std::cerr << "Invalid arguments" << "\n";
    return 1;
  }
  burukov::Graph graph = burukov::makeGraph();
  int code = 0;
  try
  {
    code = run(args, graph);
  }
  catch (...)
  {
    burukov::clearGraph(graph);
    throw;
  }
  burukov::clearGraph(graph);
  return code;
}
