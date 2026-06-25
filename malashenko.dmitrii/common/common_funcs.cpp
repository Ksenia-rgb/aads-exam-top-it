#include <common_funcs.hpp>



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

bool malashenko::parse_date_line(const std::string& line, size_t& id1, size_t& id2, size_t& dateDur)
{
  size_t len = line.size();
  if (len == 0)
  {
    return false;
  }

  size_t pos = 0;
  std::string id1Str = get_str_after_whitespace(line, pos);
  try
  {
    id1 = std::stoull(id1Str);
  }
  catch (...)
  {
    return false;
  }

  skip_whitespace(line, pos);

  size_t id2Start = pos;
  std::string id2Str = get_str_after_whitespace(line, pos);
  try
  {
    id2 = std::stoull(id2Str);
  }
  catch (...)
  {
    return false;
  }

  skip_whitespace(line, pos);


  std::string dateDurStr = get_str_after_whitespace(line, pos);

  try
  {
    dateDur = std::stoull(dateDurStr);
  }
  catch (...)
  {
    return false;
  }

  if (pos >= len)
  {
    return false;
  }
  return true;
}

size_t malashenko::skip_whitespace(const std::string& str, size_t pos)
{
    while (pos < str.size() && (str[pos] == ' '  || str[pos] == '\t' || str[pos] == '\v' || str[pos] == '\f'))
    {
        ++pos;
    }
    return pos;
}

std::string malashenko::get_str_after_whitespace(const std::string& str, size_t& pos)
{
  size_t strBegin = pos;
  if (!std::isdigit(static_cast< unsigned char >(str[pos])))
  {
    return std::string();
  }

  while (pos < str.size() && std::isdigit(static_cast< unsigned char >(str[pos])))
  {
    ++pos;
  }

  std::string newStr = str.substr(strBegin, pos);
  return newStr;
}
