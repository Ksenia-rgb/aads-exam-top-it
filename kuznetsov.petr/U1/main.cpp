#include <iostream>
#include <cstddef>
#include <fstream>
#include <limits>
#include "person.hpp"
#include "darray.hpp"

namespace kuznetsov {
  Person readPerson(std::istream& in);
  bool equalPersons(const Person& a, const Person& b);


}

int main(int argc, char** argv)
{
  namespace kuz = kuznetsov;
  std::ifstream ifile;
  std::ofstream ofile;
  std::istream* source = &std::cin;
  std::ostream* output = &std::cout;
  size_t countInp = 0, countOut = 0;
  if (argc > 3) {
    return 1;
  }

  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      std::string str = argv[i];
      if (str.find("in:") == 0) {
        std::string path = str.substr(3);
        ifile.open(path);
        if (!ifile) {
          std::cerr << "Cant open file\n";
          return 2;
        }
        source = &ifile;
        countInp++;
      } else if (str.find("out:") == 0) {
        std::string path = str.substr(4);
        ofile.open(path);
        if (!ofile) {
          std::cerr << "Cant open file\n";
          return 2;
        }
        output = &ofile;
        countOut++;
      }
    }
  }

  if (countInp > 1 || countOut > 1) {
    return 1;
  }

  kuz::darray< kuz::Person > persons = kuz::makeDarray< kuz::Person >(8);
  while (!source->eof()) {
    kuz::Person p = kuz::readPerson(*source);
    if (!source->fail()) {
      if (!kuz::containsDarray(persons, p, kuz::equalPersons)) {
        kuz::pushBackDarray(persons, p);
      }
    } else {
      source->clear();
      std::streamsize n = std::numeric_limits< std::streamsize >::max();
      source->ignore(n, '\n');
    }
  }

  for (size_t i = 0; i < persons.size; ++i) {
    *output << persons.data[i].id << ' ' << persons.data[i].info << '\n';
  }
  if (persons.size == 0) {
    *output << '\n';
  }

  kuz::clearDarray(persons);
}

kuznetsov::Person kuznetsov::readPerson(std::istream& in)
{
  size_t id;
  std::string inf;
  in >> id;
  char c;
  while (in.peek() == ' ') {
    in.get(c);
  }
  if (!in || c == '\n') {
    in.setstate(std::ios::failbit);
    return {};
  }
  in >> inf;
  return Person{id, inf};
}

bool kuznetsov::equalPersons(const Person& a, const Person& b)
{
  bool f = a.id == b.id;
  return f;
}
