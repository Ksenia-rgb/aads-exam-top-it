#include "commands.hpp"
#include "../common/io.hpp"
#include "meet.hpp"

#include <string>
#include <iostream>
#include <fstream>

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

  static void cmdRedesc(Array< Person > & persons, size_t id, const std::string & desc)
  {
    const size_t idx = findPerson(persons, id);
    if (idx == persons.size)
    {
      pushBack(persons, Person{id, desc});
      return;
    }
    persons.data[idx].info = desc;
  }

  static void cmdDeanon(Array< Person > & persons,
      Array< Meet > & meets,
      size_t anonId,
      size_t id)
  {
    if (hasDesc(persons, anonId) || !hasDesc(persons, id))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    for (size_t i = 0; i < meets.size; ++i)
    {
      if (meets.data[i].id1 == anonId)
      {
        meets.data[i].id1 = id;
      }
      else if (meets.data[i].id2 == anonId)
      {
        meets.data[i].id2 = id;
      }
    }
    Array< Meet > filtered = mArray< Meet >();
    for (size_t i = 0; i < meets.size; ++i)
    {
      if (meets.data[i].id1 != meets.data[i].id2)
      {
        pushBack(filtered, meets.data[i]);
      }
    }
    clear(meets);
    meets = filtered;
    for (size_t i = 0; i < persons.size; ++i)
    {
      if (persons.data[i].id == anonId)
      {
        for (size_t j = i; j < persons.size - 1; ++j)
        {
          persons.data[j] = persons.data[j + 1];
        }
        --persons.size;
        break;
      }
    }
  }

  static void printMeetsSorted(const Array< Meet > & meets,
      size_t id,
      std::ostream & out)
  {
    Array< Meet > tmp = mArray< Meet >();
    for (size_t i = 0; i < meets.size; ++i)
    {
      if (meets.data[i].id1 == id || meets.data[i].id2 == id)
      {
        pushBack(tmp, meets.data[i]);
      }
    }
    for (size_t i = 0; i < tmp.size; ++i)
    {
      for (size_t j = i + 1; j < tmp.size; ++j)
      {
        const size_t othI = tmp.data[i].id1 == id ? tmp.data[i].id2 : tmp.data[i].id1;
        const size_t othJ = tmp.data[j].id1 == id ? tmp.data[j].id2 : tmp.data[j].id1;
        if (othI > othJ || (othI == othJ && tmp.data[i].duration > tmp.data[j].duration))
        {
          const Meet m = tmp.data[i];
          tmp.data[i] = tmp.data[j];
          tmp.data[j] = m;
        }
      }
    }
    for (size_t i = 0; i < tmp.size; ++i)
    {
      const size_t other = tmp.data[i].id1 == id ? tmp.data[i].id2 : tmp.data[i].id1;
      out << other << " " << tmp.data[i].duration << "\n";
    }
    clear(tmp);
  }

  static void cmdLessGreater(const Array< Meet > & meets,
      size_t id,
      size_t time,
      bool less,
      std::ostream & out)
  {
    Array< Meet > tmp = mArray< Meet >();
    for (size_t i = 0; i < meets.size; ++i)
    {
      if (meets.data[i].id1 != id && meets.data[i].id2 != id)
      {
        continue;
      }
      if (less && meets.data[i].duration < time)
      {
        pushBack(tmp, meets.data[i]);
      }
      else if (!less && meets.data[i].duration > time)
      {
        pushBack(tmp, meets.data[i]);
      }
    }
    for (size_t i = 0; i < tmp.size; ++i)
    {
      for (size_t j = i + 1; j < tmp.size; ++j)
      {
        const size_t othI = tmp.data[i].id1 == id ? tmp.data[i].id2 : tmp.data[i].id1;
        const size_t othJ = tmp.data[j].id1 == id ? tmp.data[j].id2 : tmp.data[j].id1;
        if (othI > othJ || (othI == othJ && tmp.data[i].duration > tmp.data[j].duration))
        {
          const Meet m = tmp.data[i];
          tmp.data[i] = tmp.data[j];
          tmp.data[j] = m;
        }
      }
    }
    for (size_t i = 0; i < tmp.size; ++i)
    {
      const size_t other = tmp.data[i].id1 == id ? tmp.data[i].id2 : tmp.data[i].id1;
      out << other << " " << tmp.data[i].duration << "\n";
    }
    clear(tmp);
  }

  static void cmdCommons(const Array< Meet > & meets,
      size_t id1,
      size_t id2,
      std::ostream & out)
  {
    Array< size_t > commons = mArray< size_t >();
    for (size_t i = 0; i < meets.size; ++i)
    {
      const size_t a = meets.data[i].id1;
      const size_t b = meets.data[i].id2;
      size_t other = meets.size;
      if (a == id1)
      {
        other = b;
      }
      else if (b == id1)
      {
        other = a;
      }
      if (other == meets.size || other == id1 || other == id2)
      {
        continue;
      }
      bool met2 = false;
      for (size_t j = 0; j < meets.size; ++j)
      {
        if ((meets.data[j].id1 == id2 && meets.data[j].id2 == other)
            || (meets.data[j].id2 == id2 && meets.data[j].id1 == other))
        {
          met2 = true;
          break;
        }
      }
      if (!met2)
      {
        continue;
      }
      bool found = false;
      for (size_t k = 0; k < commons.size; ++k)
      {
        if (commons.data[k] == other)
        {
          found = true;
          break;
        }
      }
      if (!found)
      {
        pushBack(commons, other);
      }
    }
    for (size_t i = 0; i < commons.size; ++i)
    {
      for (size_t j = i + 1; j < commons.size; ++j)
      {
        if (commons.data[i] > commons.data[j])
        {
          const size_t tmp = commons.data[i];
          commons.data[i] = commons.data[j];
          commons.data[j] = tmp;
        }
      }
    }
    for (size_t i = 0; i < commons.size; ++i)
    {
      out << commons.data[i] << "\n";
    }
    clear(commons);
  }

  static void cmdOutPersons(const Array< Person > & persons, const std::string & filename)
  {
    std::ofstream fout(filename);
    if (!fout.is_open())
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    for (size_t i = 0; i < persons.size; ++i)
    {
      if (!persons.data[i].info.empty())
      {
        fout << persons.data[i].id << " " << persons.data[i].info << "\n";
      }
    }
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
      else if (cmd == "deanon")
      {
        size_t anonId = 0;
        size_t id = 0;
        if (!(in >> anonId >> id))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        cmdDeanon(persons, meets, anonId, id);
      }
      else if (cmd == "redesc")
      {
        size_t id = 0;
        if (!(in >> id))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        std::string desc;
        char ch = 0;
        while (in.get(ch) && ch != '"')
        {
        }
        while (in.get(ch) && ch != '"')
        {
          desc += ch;
        }
        cmdRedesc(persons, id, desc);
      }
      else if (cmd == "meets")
      {
        size_t id = 0;
        if (!(in >> id))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        printMeetsSorted(meets, id, out);
      }
      else if (cmd == "less")
      {
        size_t time = 0;
        size_t id = 0;
        if (!(in >> time >> id))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        cmdLessGreater(meets, id, time, true, out);
      }
      else if (cmd == "greater")
      {
        size_t time = 0;
        size_t id = 0;
        if (!(in >> time >> id))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        cmdLessGreater(meets, id, time, false, out);
      }
      else if (cmd == "commons")
      {
        size_t id1 = 0;
        size_t id2 = 0;
        if (!(in >> id1 >> id2))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        cmdCommons(meets, id1, id2, out);
      }
      else if (cmd == "out-persons")
      {
        std::string filename;
        if (!(in >> filename))
        {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        cmdOutPersons(persons, filename);
      }
      else
      {
        out << "<INVALID COMMAND>\n";
      }
    }
  }
}
