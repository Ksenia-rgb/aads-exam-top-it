#include <fstream>
#include <common_funcs.hpp>


int main(int argc, char ** argv)
{
  using namespace malashenko;
  if (argc > 3)
  {
    std::cerr << "Wrong amount of parameters";
    return 0;
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
        std::cerr << "Can't be 2 input files\n";
        return 1;
      }

      in_file = arg.substr(3);

      if (in_file.empty())
      {
        std::cerr << "Wrong name for input file\n";
        return 1;
      }

    }
    else if (arg.size() >= 4 && arg.substr(0, 4) == "out:")
    {
      if (!out_file.empty())
      {
        std::cerr << "Can't be 2 output files\n";
      }

      out_file = arg.substr(4);

      if (out_file.empty())
      {
        std::cerr << "Wrong name for output file\n";
        return 1;
      }
    }
    else
    {
      std::cerr << "Unknown parametr\n";
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
      std::cerr << "Can't open the input file\n";
      return 2;
    }
    input = &in_fs;
  }

  Vec< Person > persons;
  init(persons, 8);

  size_t success = 0;
  size_t skiped = 0;

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
        std::cerr << "Can't open the output file\n";
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
