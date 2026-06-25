#include "meet.hpp"
#include "../common/io.hpp"

#include <string>
#include <iostream>

namespace ulanova
{
  Array< Meet > readMeets(std::istream & in)
  {
    Array< Meet > arr = mArray< Meet >();
    size_t id1 = 0;
    size_t id2 = 0;
    size_t duration = 0;
    while (in >> id1 >> id2 >> duration)
    {
      if (id1 == id2)
      {
        continue;
      }
      pushBack(arr, Meet{id1, id2, duration});
    }
    if (!in.eof())
    {
      std::cerr << "Invalid meet data\n";
      clear(arr);
    }
    return arr;
  }
}
