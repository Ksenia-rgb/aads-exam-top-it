#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "person_table.hpp"

namespace zubarev
{
  void cmd_anons(std::istream&, std::ostream& out, PersonTable& table);
  void cmd_deanon(std::istream& in, std::ostream& out, PersonTable& table);
  void cmd_desc(std::istream& in, std::ostream& out, PersonTable& table);
  void cmd_redesc(std::istream& in, std::ostream& out, PersonTable& table);
  void cmd_meets(std::istream& in, std::ostream& out, PersonTable& table);
  void cmd_commons(std::istream& in, std::ostream& out, PersonTable& table);
  void cmd_less(std::istream& in, std::ostream& out, PersonTable& table);
  void cmd_greater(std::istream& in, std::ostream& out, PersonTable& table);
  void cmd_out_persons(std::istream& in, std::ostream& out, PersonTable& table);
}
#endif
