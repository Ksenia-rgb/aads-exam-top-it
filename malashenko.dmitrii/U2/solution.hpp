#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <iostream>
#include <vector.hpp>
#include <person.hpp>
#include <common_funcs.hpp>
namespace malashenko
{

  void readPersonsData(std::istream& in, Vec< Person >& persons);
  void readDateData(std::istream& in, Vec< Person >& persons,
                    Vec< std::pair< size_t, size_t > >& daters,
                    Vec< size_t >& durations);
}

#endif