#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <iostream>
#include <vector.hpp>
#include <person.hpp>
#include <common_funcs.hpp>
namespace malashenko
{
  void readPersonsData(std::istream& in, Vec< Person >& persons);
  void readDateData(std::istream& in, Vec< Person >& persons);
}

#endif