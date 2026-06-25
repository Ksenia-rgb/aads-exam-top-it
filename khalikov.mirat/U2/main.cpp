#include <iostream>
#include <string>
#include <fstream>
#include "list.hpp"
#include "person.hpp"
#include <map>
#include <limits>

namespace khalikov {

  struct Data
  {
    khalikov::List< khalikov::Person > *people;
    khalikov::List< khalikov::Meet > *meets;
  };

  void output(List< khalikov::Person > *h, std::ostream &out)
  {
    List< khalikov::Person > *curr = h;
    while (curr) {
      out << curr->val.id << ' ' << curr->val.info << '\n';
      curr = curr->next;
    }
  }

  bool InRead(int argc, char **argv, std::string &inFile, std::string &dataFile)
  {
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if (arg.length() >= 3 && arg[0] == 'i' && arg[1] == 'n' && arg[2] == ':') {
        if (!inFile.empty()) {
          return false;
        }
        inFile = arg.substr(3);
      }
      else if (arg.length() >= 5 && arg[0] == 'd' && arg[1] == 'a' && arg[2] == 't' && arg[3] == 'a' && arg[4] == ':') {
        if (!dataFile.empty()) {
          return false;
        }
        dataFile = arg.substr(5);
      }
      else {
        return false;
      }
    }
    return true;
  }

}



int main(int argc, char **argv)
{
  if (argc > 3 || argc < 2) {
    return 1;
  }
  std::string inFile = "";
  std::string dataFile = "";
  if (!khalikov::InRead(argc, argv, inFile, dataFile)) {
    return 1;
  }

  std::ifstream inF;
  if (!inFile.empty()) {
    inF.open(inFile);
    if (!inF.is_open()) {
      return 2;
    }
  }

  khalikov::List< khalikov::Person > *ph = nullptr;

  while (inF.peek() != EOF) {
    khalikov::getPerson(inF, ph);
  }
  inF.close();

  std::ifstream dataF(dataFile);
  if (!dataF.is_open()) {
    khalikov::clear(ph);
    return 2;
  }

  khalikov::List< khalikov::Meet > *mh = nullptr;

  while (dataF.peek() != EOF) {
    if (!khalikov::getMeet(dataF, mh)) {
      khalikov::clear(ph);
      khalikov::clear(mh);
      return 3;
    }
  }
  dataF.close();

  using cmd_t = void (*)(std::ostream &, std::istream &, khalikov::Data &);
  std::map< std::string, cmd_t > cmds;

  cmds["anons"] = khalikov::anons

  khalikov::Data d{ph, mh};
  std::string cmd;
  while (std::cin >> cmd) {
    try {
      cmds.at(cmd)(std::cout, std::cin, d);
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      auto toignore = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(toignore, '\n');
    }
  }
  if (!std::cin.eof()) {
    std::cerr << "Bad input\n";
    return 1;
  }
}
