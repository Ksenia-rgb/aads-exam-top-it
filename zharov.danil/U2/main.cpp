#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <hash_table.hpp>
#include <io.hpp>
#include "commands.hpp"

int main(int argc, char** argv)
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Invalid arguments\n";
    return 0;
  }
  std::string inFile;
  std::string dataFile;
  bool hasIn = false;
  bool hasData = false;
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);
    if (arg.size() > 3 && arg.substr(0, 3) == "in:")
    {
      if (hasIn)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      inFile = arg.substr(3);
      hasIn = true;
    }
    else if (arg.size() > 5 && arg.substr(0, 5) == "data:")
    {
      if (hasData)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      dataFile = arg.substr(5);
      hasData = true;
    }
    else
    {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }
  if (!hasData)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  zharov::Array< zharov::Person > persons = zharov::makeArray< zharov::Person >(10);
  if (hasIn)
  {
    std::ifstream file_in(inFile);
    if (!file_in.is_open())
    {
      std::cerr << "Cannot open file\n";
      zharov::clear(persons);
      return 2;
    }
    size_t accepted = 0;
    size_t ignored = 0;
    zharov::readPersons(file_in, persons, accepted, ignored);
  }
  std::ifstream file_data(dataFile);
  if (!file_data.is_open())
  {
    std::cerr << "Cannot open file\n";
    zharov::clear(persons);
    return 2;
  }
  zharov::Array< zharov::Meet > meets = zharov::makeArray< zharov::Meet >(10);
  if (!zharov::readMeets(file_data, meets))
  {
    std::cerr << "Invalid data\n";
    zharov::clear(persons);
    zharov::clear(meets);
    return 3;
  }

  zharov::HashTable< std::string, zharov::Cmd > cmds =
    zharov::makeHashTable< std::string, zharov::Cmd >(8);
  zharov::insert< std::string, zharov::Cmd >(cmds, std::string("deanon"), zharov::runDeanon);
  zharov::insert< std::string, zharov::Cmd >(cmds, std::string("redesc"), zharov::runRedesc);

  zharov::HashTable< std::string, zharov::ConstCmd > constCmds =
    zharov::makeHashTable< std::string, zharov::ConstCmd >(16);
  zharov::insert< std::string, zharov::ConstCmd >(constCmds, std::string("anons"), zharov::runAnons);
  zharov::insert< std::string, zharov::ConstCmd >(constCmds, std::string("desc"), zharov::runDesc);
  zharov::insert< std::string, zharov::ConstCmd >(constCmds, std::string("meets"), zharov::runMeets);
  zharov::insert< std::string, zharov::ConstCmd >(constCmds, std::string("commons"), zharov::runCommons);
  zharov::insert< std::string, zharov::ConstCmd >(constCmds, std::string("less"), zharov::runLess);
  zharov::insert< std::string, zharov::ConstCmd >(constCmds, std::string("greater"), zharov::runGreater);
  zharov::insert< std::string, zharov::ConstCmd >(constCmds, std::string("out-persons"), zharov::runOutPersons);

  zharov::Context ctx{std::addressof(persons), std::addressof(meets)};

  std::string command;
  while (std::cin >> command)
  {
    zharov::detail::Node< zharov::Entry< std::string, zharov::Cmd > >* node =
      zharov::find(cmds, command);
    zharov::detail::Node< zharov::Entry< std::string, zharov::ConstCmd > >* constNode =
      zharov::find(constCmds, command);
    if (node == nullptr && constNode == nullptr)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    try
    {
      if (node != nullptr)
      {
        node->val.val(std::cout, std::cin, ctx);
      }
      else
      {
        constNode->val.val(std::cout, std::cin, ctx);
      }
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  zharov::clear(cmds);
  zharov::clear(constCmds);
  zharov::clear(persons);
  zharov::clear(meets);
}
