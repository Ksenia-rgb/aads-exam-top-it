#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "../common/person.hpp"
#include "meeting.hpp"
#include "storage.hpp"
#include "args.hpp"

int main(int argc, char* argv[])
{
  try
  {
    losev::Args args = losev::parseArgs(argc, argv);
    std::cout << "in: " << (args.hasIn ? args.inFile : "(stdin)") << "\n";
    std::cout << "data: " << args.dataFile << "\n";
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
