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

void malashenko::readDateData(std::istream& in, Vec< Person >& persons, Vec< std::pair< size_t, size_t > >& daters, Vec< size_t >& durations)
{
  std::string line;
  while (read_line(in, line))
  {
    size_t id1;
    size_t id2;
    size_t dateDur;
    if (parse_date_line(line, id1, id2, dateDur))
    {
      pushBack(daters, {id1, id2});
      pushBack(durations, dateDur);

      if (!containsId(persons, id1))
      {
        pushBack(persons, {id1, std::string()});
      }
      if (!containsId(persons, id2))
      {
        pushBack(persons, {id2, std::string()});
      }
    }
  }
}

