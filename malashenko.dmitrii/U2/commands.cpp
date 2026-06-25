#include "commands.hpp"

void malashenko::anons(std::ostream& out, const Vec< Person >& persons)
{
  for (size_t i = 0; i < persons.size; ++i)
  {
    if (persons.data[i].info.empty())
    {
      out << persons.data[i].id << '\n';
    }
  }
}