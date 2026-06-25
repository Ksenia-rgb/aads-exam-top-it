#include "solution.hpp"

bool malashenko::containsId(const Vec< Person > &vec, size_t id)
{
  for (size_t i = 0; i < vec.size; ++i)
  {
    if (vec.data[i].id == id)
    {
      return true;
    }
  }
  return false;
}
