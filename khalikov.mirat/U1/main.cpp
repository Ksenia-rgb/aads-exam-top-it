#include <iostream>
#include <string>
#include <fstream>
#include "list.hpp"
#include "person.hpp"

namespace khalikov {
  void output(List< khalikov::Person > *h, std::ostream &out)
  {
    List< khalikov::Person > *curr = h;
    while (curr)
    {
      out << curr->val.id << ' ' << curr->val.info << '\n';
      curr = curr->next;
    }
  }

  bool InOutRead(int argc, char **argv, std::string &inFile, std::string &outFile)
  {
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if (arg.length() >= 3 && arg[0] == 'i' && arg[1] == 'n' && arg[2] == ':') {
        if (!inFile.empty()) {
          return false;
        }
        inFile = arg.substr(3);
      }
      else if (arg.length() >= 4 && arg[0] == 'o' && arg[1] == 'u' && arg[2] == 't' && arg[3] == ':') {
        if (!outFile.empty()) {
          return false;
        }
        outFile = arg.substr(4);
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
  if (argc > 3) {
    return 1;
  }
  std::string inFile = "";
  std::string outFile = "";
  if (!khalikov::InOutRead(argc, argv, inFile, outFile)) {
    return 1;
  }
  std::ifstream inF;
  if (!inFile.empty()) {
    inF.open(inFile);
    if (!inF.is_open()) {
      return 2;
    }
  }

  std::istream &in = inFile.empty() ? std::cin : inF;

  khalikov::List< khalikov::Person > *h = nullptr;
  size_t success = 0;
  size_t unsuccess = 0;
  while (in.peek() != EOF) {
    if (khalikov::getPerson(in, h)) {
      success++;
    }
    else {
      unsuccess++;
    }
  }

  if (!inFile.empty()) {
    inF.close();
  }

  std::ofstream outF;
  if (!outFile.empty()) {
    outF.open(outFile);
    if (!outF.is_open()) {
      return 2;
    }
  }
  std::ostream &out = outFile.empty() ? std::cout : outF;

  khalikov::output(h, out);
  khalikov::clear(h);
  if (!outFile.empty()) {
    outF.close();
  }
  std::cerr << success << ' ' << unsuccess << '\n';
}
