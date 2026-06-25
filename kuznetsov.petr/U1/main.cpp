#include <iostream>
#include <cstddef>
#include <fstream>
#include "person.hpp"
#include "darray.hpp"

namespace kuznetsov {
  Person readPerson(std::istream& in, bool& success);
  bool equalPersons(const Person& a, const Person& b);


}

int main(int argc, char** argv)
{
  namespace kuz = kuznetsov;
  std::ifstream ifile;
  std::ofstream ofile;
  std::string iPath, oPath;
  std::istream* source = &std::cin;
  std::ostream* output = &std::cout;
  size_t countInp = 0, countOut = 0;
  if (argc > 3) {
    std::cerr << "Too musn args\n";
    return 0;
  }

  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      std::string str = argv[i];
      if (str.find("in:") == 0) {
        std::string path = str.substr(3);
        iPath = path;
        countInp++;
      } else if (str.find("out:") == 0) {
        std::string path = str.substr(4);
        oPath = path;
        countOut++;
      } else {
        return 1;
      }
    }
  }

  if (countInp > 1 || countOut > 1) {
    return 1;
  }

  if (countInp == 1) {
    ifile.open(iPath);
    if (!ifile) {
      std::cerr << "Cant open file\n";
      return 2;
    }
    source = &ifile;
  }

  size_t cSucces = 0, cFail = 0;
  kuz::darray< kuz::Person > persons = kuz::makeDarray< kuz::Person >(8);
  *source >> std::ws;
  while (!source->eof()) {
    bool s = false;
    kuz::Person p = kuz::readPerson(*source, s);
    if (s && !kuz::containsDarray(persons, p, kuz::equalPersons)) {
      kuz::pushBackDarray(persons, p);
      ++cSucces;
    } else {
      ++cFail;
    }
    *source >> std::ws;
  }
  ifile.close();
  if (countOut == 1) {
    ofile.open(oPath);
    if (!ofile) {
      std::cerr << "Cant open file\n";
      kuz::clearDarray(persons);
      return 2;
    }
    output = &ofile;
  }

  for (size_t i = 0; i < persons.size; ++i) {
    *output << persons.data[i].id << ' ' << persons.data[i].info << '\n';
  }
  if (persons.size == 0) {
    *output << '\n';
  }
  std::cerr << cSucces << ' ' << cFail << '\n';
  kuz::clearDarray(persons);
}

kuznetsov::Person kuznetsov::readPerson(std::istream& in, bool& success)
{
  size_t id;
  in >> id;
  if (!in) {
    success = false;
    in.clear();
    std::string skip;
    std::getline(in, skip);
    return {};
  }
  while (in.peek() == ' ' || in.peek() == '\t') {
    in.ignore();
  }
  std::string inf;
  std::getline(in, inf);
  if (inf.empty()) {
    success = false;
    return {};
  }
  success = true;
  return Person{id, inf};
}

bool kuznetsov::equalPersons(const Person& a, const Person& b)
{
  bool f = a.id == b.id;
  return f;
}
