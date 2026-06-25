#include "io.hpp"

#include <string>
#include <iostream>

namespace ulanova
{
  bool containsId(const Array< Person > & arr, size_t id)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      if (arr.data[i].id == id)
      {
        return true;
      }
    }
    return false;
  }

  void printPersons(const Array< Person > & arr, std::ostream & out)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      out << arr.data[i].id << " " << arr.data[i].info << "\n";
    }
  }
}
