#include "list.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace bukreev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  size_t good = 0;
  size_t bad = 0;

  int processArgs(int argc, char* argv[], std::string& fin, std::string& fout);
  void input(List< Person >* people, std::istream& in);
  void output(List< Person >* people, std::ostream& out);
}

int main(int argc, char* argv[])
{
  using namespace bukreev;

  std::string fin = "", fout = "";
  int s = processArgs(argc, argv, fin, fout);
  if (s != 0)
  {
    return s;
  }

  std::istream* in = std::addressof(std::cin);
  std::ifstream infile;
  if (!fin.empty())
  {
    infile.open(fin);
    if (!infile.is_open())
    {
      return 2;
    }

    in = std::addressof(infile);
  }

  std::ostream* out = std::addressof(std::cout);
  std::ofstream outfile;
  if (!fout.empty())
  {
    outfile.open(fin);
    if (!outfile.is_open())
    {
      return 2;
    }

    out = std::addressof(outfile);
  }

  List< Person >* people;
  createList(&people);

  try
  {
    input(people, *in);
  }
  catch(std::bad_alloc& e)
  {
    deleteList(people);
    return 3;
  }

  output(people, *out);
  deleteList(people);
}

void bukreev::input(List< Person >* people, std::istream& in)
{
  std::string line;
  while (getline(in, line))
  {
    size_t i = 0;
    while (std::isdigit(line[i]) && i < line.size())
    {
      i++;
    }

    size_t id;
    try
    {
      id = std::stoi(line.substr(0, i));
    }
    catch(...)
    {
      bad++;
      continue;
    }

    bool doubleId = false;
    List< Person >* h = people->next;
    while (h != people)
    {
      if (h->val.id == id)
      {
        doubleId = true;
        break;
      }
      h = h->next;
    }

    if (doubleId)
    {
      bad++;
      continue;
    }

    while (std::isspace(line[i]) && i < line.size())
    {
      i++;
    }

    if (i == line.size())
    {
      bad++;
      continue;
    }

    std::string name = line.substr(i);

    insertListTail(people, {id, name});
    good++;
  }
}

void bukreev::output(List< Person >* people, std::ostream& out)
{
  List< Person >* h = people->next;
  while (h != people)
  {
    Person& p = h->val;
    out << p.id << ' ' << p.info << '\n';

    h = h->next;
  }

  std::cerr << good << ' ' << bad << '\n';
}

int bukreev::processArgs(int argc, char* argv[], std::string& fin, std::string& fout)
{
  if (argc > 3)
  {
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];
    if (arg.substr(0, 3) == "in:")
    {
      fin = arg.substr(3);
    }
    else if (arg.substr(0, 4) == "out:")
    {
      fout = arg.substr(4);
    }
    else
    {
      return 1;
    }
  }

  return 0;
}
