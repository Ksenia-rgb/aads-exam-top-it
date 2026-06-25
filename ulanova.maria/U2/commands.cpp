#include "commands.hpp"
#include "../U1/io.hpp"
#include "meet.hpp"

#include <string>
#include <iostream>

namespace ulanova
{
  static size_t findPerson(const Array< Person > & persons, size_t id)
  {
    for (size_t i = 0; i < persons.size; ++i)
    {
      if (persons.data[i].id == id)
      {
        return i;
      }
    }
    return persons.size;
  }

  static bool hasDesc(const Array< Person > & persons, size_t id)
  {
    const size_t idx = findPerson(persons, id);
    if (idx == persons.size)
    {
      return false;
    }
    return !persons.data[idx].info.empty();
  }

  static void cmdAnons(const Array< Person > & persons, std::ostream & out)
  {
    Array< size_t > anons = mArray< size_t >();
    for (size_t i = 0; i < persons.size; ++i)
    {
      if (persons.data[i].info.empty())
      {
        pushBack(anons, persons.data[i].id);
      }
    }
    for (size_t i = 0; i < anons.size; ++i)
    {
      for (size_t j = i + 1; j < anons.size; ++j)
      {
        if (anons.data[i] > anons.data[j])
        {
          const size_t tmp = anons.data[i];
          anons.data[i] = anons.data[j];
          anons.data[j] = tmp;
        }
      }
    }
    for (size_t i = 0; i < anons.size; ++i)
    {
      out << anons.data[i] << "\n";
    }
    clear(anons);
  }

  static void cmdDesc(const Array< Person > & persons, size_t id, std::ostream & out)
  {
    const size_t idx = findPerson(persons, id);
    if (idx == persons.size || persons.data[idx].info.empty())
    {
      out << "<ANON>\n";
      return;
    }
    out << persons.data[idx].info << "\n";
  }

  void runCommands(Array< Person > & persons,
      Array< Meet > & meets,
      std::istream & in,
      std::ostream & out)
  {
    std::string cmd;
    while (in >> cmd)
    {
      if (cmd == "anons")
      {
        cmdAnons(persons, out);
      }
      else if (cmd == "desc")
      {
        size_t id = 0;
        if (!(in >> id))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        cmdDesc(persons, id, out);
      }
      else
      {
        out << "<INVALID COMMAND>\n";
      }
    }
  }
}
