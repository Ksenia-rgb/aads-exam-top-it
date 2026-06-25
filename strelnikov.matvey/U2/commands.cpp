#include <iostream>
#include "commands.hpp"
#include "context.hpp"

namespace strelnikov
{
  void cmd_anons(Context &ctx)
  {
    std::cout << "[STUB] anons\n";
  }

  void cmd_deanon(Context &ctx, size_t anon_id, size_t id)
  {
    std::cout << "[STUB] deanon " << anon_id << " " << id << "\n";
  }

  void cmd_desc(Context &ctx, size_t id)
  {
    std::cout << "[STUB] desc " << id << "\n";
  }

  void cmd_redesc(Context &ctx, size_t id, const std::string &description)
  {
    std::cout << "[STUB] redesc " << id << " \"" << description << "\"\n";
  }

  void cmd_meets(Context &ctx, size_t id)
  {
    std::cout << "[STUB] meets " << id << "\n";
  }

  void cmd_commons(Context &ctx, size_t id1, size_t id2)
  {
    std::cout << "[STUB] commons " << id1 << " " << id2 << "\n";
  }

  void cmd_less(Context &ctx, size_t time, size_t id)
  {
    std::cout << "[STUB] less " << time << " " << id << "\n";
  }

  void cmd_greater(Context &ctx, size_t time, size_t id)
  {
    std::cout << "[STUB] greater " << time << " " << id << "\n";
  }

  void cmd_out_persons(Context &ctx, const std::string &filename)
  {
    std::cout << "[STUB] out-persons " << filename << "\n";
  }
}
