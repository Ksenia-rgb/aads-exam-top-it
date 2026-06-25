#include "solution.hpp"


bool malashenko::containsId(const Vec<Person> &vec, size_t id)
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

bool malashenko::read_line(std::istream &in, std::string &line)
{
  line.clear();
  char ch;
  while (in.get(ch))
  {
    if (ch == '\n')
    {
      return true;
    }
    if (ch == '\r')
    {
      char next;
      if (in.get(next))
      {
        if (next != '\n')
        {
          in.putback(next);
        }
      }
      return true;
    }
    line += ch;
  }
  return !line.empty();
}

bool malashenko::parse_line(const std::string &line, size_t &id, std::string &info)
{
  size_t len = line.size();
  if (len == 0)
  {
    return false;
  }

  size_t pos = 0;

  if (!std::isdigit(static_cast<unsigned char>(line[pos])))
  {
    return false;
  }

  while (pos < len && std::isdigit(static_cast<unsigned char>(line[pos])))
  {
    ++pos;
  }

  std::string idStr = line.substr(0, pos);
  try
  {
    id = std::stoull(idStr);
  }
  catch (...)
  {
    return false;
  }

  while (pos < len && line[pos] == ' ')
  {
    ++pos;
  }

  if (pos >= len)
  {
    return false;
  }

  info = line.substr(pos);
  return true;
}
