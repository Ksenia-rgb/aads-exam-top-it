#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "../common/darray.hpp"
#include "../common/person.hpp"
#include "meeting.hpp"
#include "commands.hpp"
#include "../common/hashTable.hpp"

int main(int argc, char** argv)
{
  namespace kuz = kuznetsov;
  std::ifstream ifile;
  std::ifstream idata;
  std::string iPath, dataPath;
  std::istream* source = &std::cin;
  size_t countInp = 0, countData = 0;
  if (argc > 3) {
    std::cerr << "Too many args\n";
    return 0;
  }

  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      std::string str = argv[i];
      if (str.find("in:") == 0) {
        iPath = str.substr(3);
        countInp++;
      } else if (str.find("data:") == 0) {
        dataPath = str.substr(5);
        countData++;
      } else {
        std::cerr << "Unknown arg\n";
        return 1;
      }
    }
  }

  if (countInp > 1 || countData != 1) {
    std::cerr << "Bad args\n";
    return 1;
  }

  idata.open(dataPath);
  if (!idata) {
    std::cerr << "Cant open file\n";
    return 2;
  }

  kuz::darray< kuz::Person > persons;
  if (countInp == 1) {
    ifile.open(iPath);
    if (!ifile) {
      std::cerr << "Cant open file\n";
      return 2;
    }
    source = &ifile;
    size_t cSucces = 0, cFail = 0;
    persons = kuz::readArray(*source, cSucces, cFail);
  } else {
    persons = kuz::makeDarray< kuz::Person >(8);
  }

  bool meetsOk = true;
  kuz::darray< kuz::Meeting > meets = kuz::readArrayMeets(idata, persons, meetsOk);
  if (!meetsOk) {
    std::cerr << "Bad meeting data\n";
    kuz::clearDarray(meets);
    kuz::clearDarray(persons);
    return 3;
  }

  using cmd = void (*)(std::istream&, std::ostream&, kuz::darray< kuz::Meeting >&, kuz::darray< kuz::Person >&);
  kuz::hashTable< std::string, cmd > queryCmds = kuz::makeHashTable< std::string, cmd >(8);
  kuz::hashTable< std::string, cmd > mutCmds = kuz::makeHashTable< std::string, cmd >(8);
  kuz::insertHashTable(queryCmds, std::string("anons"), kuz::anons);
  kuz::insertHashTable(queryCmds, std::string("desc"), kuz::desc);
  kuz::insertHashTable(queryCmds, std::string("meets"), kuz::meets);
  kuz::insertHashTable(queryCmds, std::string("commons"), kuz::commons);
  kuz::insertHashTable(queryCmds, std::string("less"), kuz::less);
  kuz::insertHashTable(queryCmds, std::string("greater"), kuz::greater);
  kuz::insertHashTable(mutCmds, std::string("deanon"), kuz::deanon);
  kuz::insertHashTable(mutCmds, std::string("redesc"), kuz::redesc);
  kuz::insertHashTable(mutCmds, std::string("out-persons"), kuz::out_persons);

  std::string c;
  while (std::cin >> c) {
    try {
      cmd* qfn = kuz::findHashTable(queryCmds, c);
      if (qfn) {
        (*qfn)(std::cin, std::cout, meets, persons);
        std::cout << '\n';
      } else {
        cmd* mfn = kuz::findHashTable(mutCmds, c);
        if (!mfn) {
          throw std::logic_error("cmd");
        }
        (*mfn)(std::cin, std::cout, meets, persons);
      }
    } catch (const std::logic_error&) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  kuz::clearHashTable(queryCmds);
  kuz::clearHashTable(mutCmds);
  kuz::clearDarray(meets);
  kuz::clearDarray(persons);
}
