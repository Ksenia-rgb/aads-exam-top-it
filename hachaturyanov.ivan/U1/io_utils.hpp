#ifndef IO_UTILS_HPP
#define IO_UTILS_HPP

#include "../common/list.hpp"
#include <string>

namespace hachaturyanov
{
  List< std::string > split(std::string line);
  bool isDigit(std::string str);
  std::pair< std::string, std::string > splitInTwo(std::string line);
}

#endif
