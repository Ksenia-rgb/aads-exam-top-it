#ifndef STUDILOVA_MEET_PARSER_HPP
#define STUDILOVA_MEET_PARSER_HPP

#include <person.hpp>

#include "meet.hpp"
#include "person_ops.hpp"

#include <istream>

namespace studilova
{
  bool readMeets(std::istream &input, MeetArray &meets, PersonArray &persons);
}

#endif
