#include "input_handler.hpp"

#include <cstdlib>

namespace smirnova
{
  InputHandler::InputHandler(const std::string& inputFileName)
  {
    if (!inputFileName.empty())
    {
      inputFile_.open(inputFileName);

      if (!inputFile_)
      {
        std::cerr << "Failed to open input file.\n";
        std::exit(2);
      }
    }
  }

  InputHandler::~InputHandler()
  {
    if (inputFile_.is_open())
    {
      inputFile_.close();
    }
  }

  std::istream& InputHandler::getInputStream()
  {
    if (inputFile_.is_open())
    {
      return inputFile_;
    }

    return std::cin;
  }
}

