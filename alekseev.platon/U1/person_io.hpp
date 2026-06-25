#ifndef PERSON_IO_HPP
#define PERSON_IO_HPP

#include <iosfwd>

namespace alekseev
{
  int runPersonInput(int argc,
      char** argv,
      std::istream& input,
      std::ostream& output,
      std::ostream& error);
}

#endif
