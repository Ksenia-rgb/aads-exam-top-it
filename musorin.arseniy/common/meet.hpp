#ifndef MUSORIN_MEET_HPP
#define MUSORIN_MEET_HPP
#include <cstddef>
#include <string>
namespace musorin
{
struct Meet
{
  std::size_t from;
  std::size_t to;
  std::size_t duration;
};
bool parseMeetLine(const std::string & line, Meet & meet);
}
#endif
