#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>

namespace madieva {

  struct Config {
    std::string persons_file_;
    std::string meets_file_;
  };

  Config parseArgs(int argc, char * argv[]);

}

#endif
