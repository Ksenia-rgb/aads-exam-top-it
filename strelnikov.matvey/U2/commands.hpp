#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "context.hpp"
#include <iostream>

namespace strelnikov
{
  using CmdHandler = bool (*)(std::istream &, std::ostream &, Context &);

  bool cmd_anons(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_deanon(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_desc(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_redesc(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_meets(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_commons(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_less(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_greater(std::istream &in, std::ostream &out, Context &ctx);
  bool cmd_out_persons(std::istream &in, std::ostream &out, Context &ctx);

  struct CommandEntry
  {
    const char *name;
    CmdHandler handler;
  };

  const CommandEntry cmds[] = {{"anons", cmd_anons},   {"deanon", cmd_deanon},   {"desc", cmd_desc},
                               {"redesc", cmd_redesc}, {"meets", cmd_meets},     {"commons", cmd_commons},
                               {"less", cmd_less},     {"greater", cmd_greater}, {"out-persons", cmd_out_persons}};

  const size_t cmdCnt = sizeof(cmds) / sizeof(cmds[0]);
}

#endif
