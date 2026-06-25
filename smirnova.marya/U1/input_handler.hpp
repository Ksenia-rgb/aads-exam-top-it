#ifndef SMIRNOVA_INPUT_HANDLER_HPP
#define SMIRNOVA_INPUT_HANDLER_HPP

#include <fstream>
#include <iostream>
#include <string>

namespace smirnova
{
  class InputHandler
  {
  public:
    InputHandler(const std::string& inputFileName);
    ~InputHandler();

    std::istream& getInputStream();

  private:
    std::ifstream inputFile_;
  };
}

#endif

