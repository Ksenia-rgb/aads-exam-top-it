#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>

namespace vasyakin
{
  bool splitArg(const std::string & arg, const std::string & key, std::string & value);
}

#endif
