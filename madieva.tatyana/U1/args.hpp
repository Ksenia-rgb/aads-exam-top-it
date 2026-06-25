#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>

namespace madieva {

  struct Config {
    std::string input_file_;
    std::string output_file_;
  };

  Config parseArgs(int argc, char* argv[]);

}

#endif
