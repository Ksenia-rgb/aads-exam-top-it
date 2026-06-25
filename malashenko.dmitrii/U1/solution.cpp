#include "solution.hpp"


bool malashenko::containsId(const Vec< Person >& vec, size_t id)
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

bool malashenko::read_line(std::istream& in, std::string& line)
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

size_t malashenko::parse_line(const std::string& line, size_t& id, std::string& info)
{
  size_t len = line.size();
  if (len == 0)
  {
    return 2;
  }

  size_t pos = 0;

  if (!std::isdigit(static_cast< unsigned char >(line[pos])))
  {
    return 0;
  }

  while (pos < len && std::isdigit(static_cast< unsigned char >(line[pos])))
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
    return 0;
  }

  while (pos < len && (line[pos] == ' '  || line[pos] == '\t' || line[pos] == '\v' || line[pos] == '\f'))
  {
    ++pos;
  }

  if (pos >= len)
  {
    return 0;
  }

  info = line.substr(pos);
  return 1;
}
