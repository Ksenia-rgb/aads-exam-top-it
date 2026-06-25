#include "solution.hpp"


void malashenko::readPersonsData(std::istream& in, Vec< Person >& persons)
{
  std::string line;
  while (read_line(in, line))
  {
    size_t id;
    std::string info;

    if (parse_line(line, id, info))
    {
      Person p{id, info};
      pushBack(persons, p);
    }
  }
}
