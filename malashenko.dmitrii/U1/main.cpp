#include <iostream>
#include <cstddef>
#include <fstream>
#include <string>

namespace malashenko
{
  struct Person {
    size_t id;
    std::string info;
  };

  template< class T >
  struct Vec {
    T* data;
    size_t size, capacity;
  };

  template< class T >
  void init(Vec< T >& vec, size_t cap)
  {
    vec.data = new T[cap];
    vec.capacity = cap;
    vec.size = 0;
  }

  template< class T >
  void pushBack(Vec< T >& vec, T val)
  {
    if (vec.size >= vec.capacity)
    {
      size_t new_capacity = vec.capacity * 2;
      T* new_data = new T[new_capacity];
      for (size_t i = 0; i < vec.size; ++i)
      {
        new_data[i] = vec.data[i];
      }
      delete[] vec.data;
      vec.data = new_data;
      vec.capacity = new_capacity;
    }
    vec.data[vec.size++] = val;
  }

  template <typename T>
  void destroy(Vec< T >& vec)
  {
    delete[] vec.data;
    vec.data = nullptr;
    vec.size = 0;
    vec.capacity = 0;
  }

  bool containsId(const Vec< Person >& vec, size_t id)
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

  bool read_line(std::istream& in, std::string& line)
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

bool parse_line(const std::string& line, size_t& id, std::string& info) {
    size_t len = line.size();
    if (len == 0) {
        return false;
    }

    size_t pos = 0;

    while (pos < len && line[pos] != ' ') {
        ++pos;
    }

    std::string idStr = line.substr(0, pos);
    try
    {
      id = std::stoull(idStr);
    }
    catch(...)
    {
      return false;
    }


    while (pos < len && line[pos] == ' ')
    {
      ++pos;
    }

    if (pos >= len) {
        return false;
    }

    info = line.substr(pos);
    return true;
}
}

int main(int argc, char ** argv)
{
  using namespace malashenko;
  if (argc > 3)
  {
    return 1;
  }
  std::string in_file;
  std::string out_file;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.size() >= 3 && arg.substr(0, 3) == "in:")
    {
      if (!in_file.empty())
      {
        return 1;
      }

      in_file = arg.substr(3);

      if (in_file.empty())
      {
        return 1;
      }

    }
    else if (arg.size() >= 4 && arg.substr(0, 4) == "out:")
    {
      if (!out_file.empty())
      {
        return 1;
      }

      out_file = arg.substr(4);

      if (out_file.empty())
      {
        return 1;
      }
    }
    else
    {
      return 1;
    }
  }

  std::istream *input = &std::cin;
  std::ifstream in_fs;

  if (!in_file.empty())
  {
    in_fs.open(in_file);
    if (!in_fs)
    {
      return 2;
    }
    input = &in_fs;
  }

  Vec< Person > persons;
  init(persons, 8);

  size_t success = 0;
  size_t skiped = 0;
  while (input)
  {
    size_t id;
    in_fs >> id;
  }

  std::string line;
  while (read_line(*input, line))
  {
    size_t id;
    std::string info;

    if (parse_line(line, id, info))
    {
      if (containsId(persons, id))
      {
        ++skiped;
      }
      else
      {
        Person p{id, info};
        pushBack(persons, p);
        ++success;
      }
    }
    else
    {
      ++skiped;
    }
  }

    if (!in_file.empty())
    {
        in_fs.close();
    }

    std::ostream* output = &std::cout;
    std::ofstream out_fs;

    if (!out_file.empty())
    {
      out_fs.open(out_file);
      if (!out_fs.is_open())
      {
        destroy(persons);
        return 2;
      }
      output = &out_fs;
    }

    for (size_t i = 0; i < persons.size; ++i)
    {
      *output << persons.data[i].id << " " << persons.data[i].info << '\n';
    }

    std::cerr << success << " " << skiped << "\n";

    if (!out_file.empty()) {
        out_fs.close();
    }

    destroy(persons);

    return 0;
}