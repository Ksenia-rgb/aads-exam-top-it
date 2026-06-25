#ifndef COMMON_FUNCS_HPP
#define COMMON_FUNCS_HPP
#include <iostream>
#include <vector.hpp>
#include <person.hpp>
namespace malashenko
{
  bool read_line(std::istream& in, std::string& line);
  bool parse_line(const std::string& line, size_t& id, std::string& info);
  bool parse_date_line(const std::string& line, size_t& id1, size_t& id2, size_t& dateDur);
  void skip_whitespace(const std::string& str, size_t& begin);
  std::string get_str_after_whitespace(const std::string& str, size_t& begin);

  bool containsId(const Vec< Person > &vec, size_t id);
}


#endif