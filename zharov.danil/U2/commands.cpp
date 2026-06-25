#include "commands.hpp"
#include <fstream>
#include <stdexcept>
#include <io.hpp>
#include <utility>

namespace
{
  bool hasAnonId(const zharov::Array< size_t >& arr, size_t id)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      if (arr.data[i] == id)
      {
        return true;
      }
    }
    return false;
  }

  void selectionSort(zharov::Array< size_t >& arr)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      size_t minIdx = i;
      for (size_t j = i + 1; j < arr.size; ++j)
      {
        if (arr.data[j] < arr.data[minIdx])
        {
          minIdx = j;
        }
      }
      std::swap(arr.data[i], arr.data[minIdx]);
    }
  }

  bool personExists(const zharov::Array< zharov::Person >& persons,
    const zharov::Array< zharov::Meet >& meets, size_t id)
  {
    if (zharov::hasId(persons, id))
    {
      return true;
    }
    for (size_t i = 0; i < meets.size; ++i)
    {
      if (meets.data[i].id1 == id || meets.data[i].id2 == id)
      {
        return true;
      }
    }
    return false;
  }

  bool isAnon(const zharov::Array< zharov::Person >& persons,
    const zharov::Array< zharov::Meet >& meets, size_t id)
  {
    if (zharov::hasId(persons, id))
    {
      return false;
    }
    for (size_t i = 0; i < meets.size; ++i)
    {
      if (meets.data[i].id1 == id || meets.data[i].id2 == id)
      {
        return true;
      }
    }
    return false;
  }

  void sortMeetEntries(zharov::Array< std::pair< size_t, size_t > >& arr)
  {
    for (size_t i = 0; i < arr.size; ++i)
    {
      size_t minIdx = i;
      for (size_t j = i + 1; j < arr.size; ++j)
      {
        if (arr.data[j].first < arr.data[minIdx].first ||
            (arr.data[j].first == arr.data[minIdx].first &&
             arr.data[j].second < arr.data[minIdx].second))
        {
          minIdx = j;
        }
      }
      std::swap(arr.data[i], arr.data[minIdx]);
    }
  }

  void collectMeets(const zharov::Array< zharov::Meet >& meets, size_t id,
    zharov::Array< std::pair< size_t, size_t > >& result)
  {
    for (size_t i = 0; i < meets.size; ++i)
    {
      if (meets.data[i].id1 == id)
      {
        zharov::pushBack(result, std::make_pair(meets.data[i].id2, meets.data[i].duration));
      }
      else if (meets.data[i].id2 == id)
      {
        zharov::pushBack(result, std::make_pair(meets.data[i].id1, meets.data[i].duration));
      }
    }
    sortMeetEntries(result);
  }
}

void zharov::runAnons(std::ostream& out, std::istream&, const Context& ctx)
{
  Array< size_t > anons = makeArray< size_t >(ctx.meets->size * 2 + 1);
  for (size_t i = 0; i < ctx.meets->size; ++i)
  {
    size_t id1 = ctx.meets->data[i].id1;
    size_t id2 = ctx.meets->data[i].id2;
    if (!hasId(*ctx.persons, id1) && !hasAnonId(anons, id1))
    {
      pushBack(anons, id1);
    }
    if (!hasId(*ctx.persons, id2) && !hasAnonId(anons, id2))
    {
      pushBack(anons, id2);
    }
  }
  selectionSort(anons);
  if (anons.size == 0)
  {
    out << "\n";
  }
  for (size_t i = 0; i < anons.size; ++i)
  {
    out << anons.data[i] << "\n";
  }
  clear(anons);
}

void zharov::runDesc(std::ostream& out, std::istream& in, const Context& ctx)
{
  size_t id = 0;
  if (!(in >> id))
  {
    throw std::invalid_argument("");
  }
  if (!personExists(*ctx.persons, *ctx.meets, id))
  {
    throw std::invalid_argument("");
  }
  in >> std::ws;
  if (in.peek() == '"')
  {
    in.get();
    std::string desc;
    std::getline(in, desc, '"');
    for (size_t i = 0; i < ctx.persons->size; ++i)
    {
      if (ctx.persons->data[i].id == id)
      {
        ctx.persons->data[i].info = desc;
        return;
      }
    }
    Person p;
    p.id = id;
    p.info = desc;
    pushBack(*ctx.persons, p);
    return;
  }
  for (size_t i = 0; i < ctx.persons->size; ++i)
  {
    if (ctx.persons->data[i].id == id)
    {
      out << ctx.persons->data[i].info << "\n";
      return;
    }
  }
  out << "<ANON>\n";
}

void zharov::runMeets(std::ostream& out, std::istream& in, const Context& ctx)
{
  size_t id = 0;
  if (!(in >> id))
  {
    throw std::invalid_argument("");
  }
  if (!personExists(*ctx.persons, *ctx.meets, id))
  {
    throw std::invalid_argument("");
  }
  Array< std::pair< size_t, size_t > > entries =
    makeArray< std::pair< size_t, size_t > >(ctx.meets->size + 1);
  collectMeets(*ctx.meets, id, entries);
  if (entries.size == 0)
  {
    out << "\n";
  }
  for (size_t i = 0; i < entries.size; ++i)
  {
    out << entries.data[i].first << " " << entries.data[i].second << "\n";
  }
  clear(entries);
}

void zharov::runCommons(std::ostream& out, std::istream& in, const Context& ctx)
{
  size_t id1 = 0;
  size_t id2 = 0;
  if (!(in >> id1 >> id2))
  {
    throw std::invalid_argument("");
  }
  if (!personExists(*ctx.persons, *ctx.meets, id1) ||
      !personExists(*ctx.persons, *ctx.meets, id2))
  {
    throw std::invalid_argument("");
  }
  Array< size_t > contacts1 = makeArray< size_t >(ctx.meets->size * 2 + 1);
  for (size_t i = 0; i < ctx.meets->size; ++i)
  {
    if (ctx.meets->data[i].id1 == id1 && !hasAnonId(contacts1, ctx.meets->data[i].id2))
    {
      pushBack(contacts1, ctx.meets->data[i].id2);
    }
    else if (ctx.meets->data[i].id2 == id1 && !hasAnonId(contacts1, ctx.meets->data[i].id1))
    {
      pushBack(contacts1, ctx.meets->data[i].id1);
    }
  }
  Array< size_t > commons = makeArray< size_t >(ctx.meets->size + 1);
  for (size_t i = 0; i < ctx.meets->size; ++i)
  {
    size_t other = 0;
    bool found = false;
    if (ctx.meets->data[i].id1 == id2)
    {
      other = ctx.meets->data[i].id2;
      found = true;
    }
    else if (ctx.meets->data[i].id2 == id2)
    {
      other = ctx.meets->data[i].id1;
      found = true;
    }
    if (found && hasAnonId(contacts1, other) && !hasAnonId(commons, other))
    {
      pushBack(commons, other);
    }
  }
  selectionSort(commons);
  if (commons.size == 0)
  {
    out << "\n";
  }
  for (size_t i = 0; i < commons.size; ++i)
  {
    out << commons.data[i] << "\n";
  }
  clear(contacts1);
  clear(commons);
}

void zharov::runLess(std::ostream& out, std::istream& in, const Context& ctx)
{
  size_t time = 0;
  size_t id = 0;
  if (!(in >> time >> id))
  {
    throw std::invalid_argument("");
  }
  if (!personExists(*ctx.persons, *ctx.meets, id))
  {
    throw std::invalid_argument("");
  }
  Array< std::pair< size_t, size_t > > entries =
    makeArray< std::pair< size_t, size_t > >(ctx.meets->size + 1);
  collectMeets(*ctx.meets, id, entries);
  bool anyLess = false;
  for (size_t i = 0; i < entries.size; ++i)
  {
    if (entries.data[i].second < time)
    {
      out << entries.data[i].first << " " << entries.data[i].second << "\n";
      anyLess = true;
    }
  }
  if (!anyLess)
  {
    out << "\n";
  }
  clear(entries);
}

void zharov::runGreater(std::ostream& out, std::istream& in, const Context& ctx)
{
  size_t time = 0;
  size_t id = 0;
  if (!(in >> time >> id))
  {
    throw std::invalid_argument("");
  }
  if (!personExists(*ctx.persons, *ctx.meets, id))
  {
    throw std::invalid_argument("");
  }
  Array< std::pair< size_t, size_t > > entries =
    makeArray< std::pair< size_t, size_t > >(ctx.meets->size + 1);
  collectMeets(*ctx.meets, id, entries);
  bool anyGreater = false;
  for (size_t i = 0; i < entries.size; ++i)
  {
    if (entries.data[i].second > time)
    {
      out << entries.data[i].first << " " << entries.data[i].second << "\n";
      anyGreater = true;
    }
  }
  if (!anyGreater)
  {
    out << "\n";
  }
  clear(entries);
}

void zharov::runOutPersons(std::ostream& out, std::istream& in, const Context& ctx)
{
  std::string filename;
  if (!(in >> filename))
  {
    throw std::invalid_argument("");
  }
  std::ofstream file(filename, std::ios::app);
  if (!file.is_open())
  {
    throw std::invalid_argument("");
  }
  if (ctx.persons->size == 0)
  {
    out << "\n";
    return;
  }
  writePersons(out, *ctx.persons);
  writePersons(file, *ctx.persons);
}

void zharov::runDeanon(std::ostream&, std::istream& in, Context& ctx)
{
  size_t anonId = 0;
  size_t id = 0;
  if (!(in >> anonId >> id))
  {
    throw std::invalid_argument("");
  }
  if (!isAnon(*ctx.persons, *ctx.meets, anonId) || !hasId(*ctx.persons, id))
  {
    throw std::invalid_argument("");
  }
  for (size_t i = 0; i < ctx.meets->size; ++i)
  {
    if (ctx.meets->data[i].id1 == anonId)
    {
      ctx.meets->data[i].id1 = id;
    }
    if (ctx.meets->data[i].id2 == anonId)
    {
      ctx.meets->data[i].id2 = id;
    }
  }
  size_t write = 0;
  for (size_t i = 0; i < ctx.meets->size; ++i)
  {
    if (ctx.meets->data[i].id1 != ctx.meets->data[i].id2)
    {
      ctx.meets->data[write++] = ctx.meets->data[i];
    }
  }
  ctx.meets->size = write;
}

void zharov::runRedesc(std::ostream&, std::istream& in, Context& ctx)
{
  size_t id = 0;
  if (!(in >> id))
  {
    throw std::invalid_argument("");
  }
  if (!personExists(*ctx.persons, *ctx.meets, id))
  {
    throw std::invalid_argument("");
  }
  char ch = 0;
  while (in.get(ch) && ch != '"') {}
  if (!in)
  {
    throw std::invalid_argument("");
  }
  std::string desc;
  if (!std::getline(in, desc, '"'))
  {
    throw std::invalid_argument("");
  }
  for (size_t i = 0; i < ctx.persons->size; ++i)
  {
    if (ctx.persons->data[i].id == id)
    {
      ctx.persons->data[i].info = desc;
      return;
    }
  }
  Person p;
  p.id = id;
  p.info = desc;
  pushBack(*ctx.persons, p);
}
