#include <iostream>
#include <fstream>
#include <string>
#include "person.hpp"

int main(int argc, char** argv)
{
  if (argc > 3)
  {
    std::cerr << "Error: Too many arguments\n";
    return 0;
  }

  std::string file_in = "";
  std::string file_out = "";

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (!arg.find("in:"))
    {
      file_in = arg.substr(3);
    }
    else if (!arg.find("out:"))
    {
      file_out = arg.substr(4);
    }
    else
    {
      return 1;
    }
  }

  std::istream* in = &std::cin;
  std::ifstream fin;

  if (file_in != "")
  {
    fin.open(file_in);
    if (!fin.is_open())
    {
      return 1;
    }
    in = &fin;
  }

  if (in->peek() == std::char_traits<char>::eof())
  {
    std::ostream* out = &std::cout;
    std::ofstream fout;
    if (file_out != "")
    {
      fout.open(file_out);
      if (!fout.is_open())
      {
        return 1;
      }
      out = &fout;
    }
    *out << "\n";
    return 0;
  }

  petrov::Person* vec = nullptr;
  size_t s = 0, c = 0, ok = 0, err = 0;
  while(*in)
  {
    size_t id_v;
    if (!(*in >> id_v))
    {
      if (in->eof())
      {
        break;
      }
      in->clear();
      std::string trash;
      if (std::getline(*in, trash))
      {
        size_t q = 0;
        for (size_t i = 0; i < trash.size(); ++i)
        {
          if (trash[i] != ' ' && trash[i] != '\n' && trash[i] != '\r' && trash[i] != '\t')
          {
            q = 1;
            break;
          }
        }
        err += q;
      }
      continue;
    }
    std::string inf;
    std::getline(*in, inf);
    size_t st = 0;
    while (st < inf.size() && (inf[st] == ' ' || inf[st] == '\n' || inf[st] == '\r' || inf[st] == '\t'))
    {
      st++;
    }
    if (st < inf.size())
    {
      inf = inf.substr(st);
    }
    else
    {
      inf = "";
    }
    if (inf.size() > 0 && inf[inf.size() - 1] == '\r')
    {
      inf = inf.substr(0, inf.size() - 1);
    }
    if (inf == "")
    {
      err++;
      continue;
    }
    petrov::Person p;
    p.id = id_v;
    p.info = inf;

    if (petrov::is_dubl(vec, p, s) == 0)
    {
      err++;
      continue;
    }
    if (s == c)
    {
      size_t new_c = 2;
      if (c != 0)
      {
        new_c = c * 2;
      }
      petrov::Person* new_v = new petrov::Person[new_c];
      for (size_t i = 0; i < s; ++i)
      {
        new_v[i] = vec[i];
      }
      delete[] vec;
      vec = new_v;
      c = new_c;
    }
    vec[s] = p;
    s++;
    ok++;
  }

  std::ostream* out = &std::cout;
  std::ofstream fout;

  if (file_out != "")
  {
    fout.open(file_out);
    if (!fout.is_open())
    {
      delete[] vec;
      return 1;
    }
    out = &fout;
  }

  for (size_t i = 0; i < s; ++i)
  {
    *out << vec[i].id << " " << vec[i].info << "\n";
  }
  std::cerr << ok << " " << err << "\n";
  delete[] vec;
  return 0;
}
