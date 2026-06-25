#include <io.hpp>
#include <string>

bool zharov::parseLine(const std::string& str, Person& p)
{
  if (str.empty())
  {
    return false;
  }
  size_t pos = 0;
  size_t id = 0;
  try
  {
    id = std::stoul(str, &pos);
  }
  catch (...)
  {
    return false;
  }
  while (pos < str.size() && (str[pos] == ' ' || str[pos] == '\t'))
  {
    ++pos;
  }
  if (pos == str.size())
  {
    return false;
  }
  p.id = id;
  p.info = str.substr(pos);
  return true;
}

bool zharov::hasId(const Array< Person >& arr, size_t id)
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

void zharov::readPersons(std::istream& in, Array< Person >& persons,
  size_t& accepted, size_t& ignored)
{
  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty())
    {
      continue;
    }
    Person p;
    if (!parseLine(line, p))
    {
      ++ignored;
      continue;
    }
    if (hasId(persons, p.id))
    {
      ++ignored;
      continue;
    }
    pushBack(persons, p);
    ++accepted;
  }
}

void zharov::writePersons(std::ostream& out, const Array< Person >& persons)
{
  for (size_t i = 0; i < persons.size; ++i)
  {
    out << persons.data[i].id << " " << persons.data[i].info << "\n";
  }
}
