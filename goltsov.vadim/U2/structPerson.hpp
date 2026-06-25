#ifndef STRUCTPERSON_HPP
#define STRUCTPERSON_HPP
#include <hashtable.hpp>
#include <iosfwd>
#include <string>
namespace goltsov
{
  struct Person
  {
    size_t id;
    std::string info;
  };
  struct Meet
  {
    size_t id_to;
    size_t length;
  };
  struct Meet_arr
  {
    size_t id;
    List< Meet >* data;
  };
}
#endif
