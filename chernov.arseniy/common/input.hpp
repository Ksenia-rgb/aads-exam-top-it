#ifndef INPUT_HPP
#define INPUT_HPP

#include <iosfwd>
#include <string>
#include "meeting.hpp"
#include "person.hpp"
#include "vector.hpp"

namespace chernov {

  bool parseArgsU1(int argc, char ** argv, std::string & inFile, std::string & outFile);
  bool parseArgsU2(int argc, char ** argv, std::string & inFile, std::string & dataFile);
  int readPersonsFromStream(std::istream & in, Vector< Person > & persons, size_t & ignored);
  int readPersonsFromFile(const std::string & filename, Vector< Person > & persons, size_t & ignored);
  int readMeetingsFromStream(std::istream & in, Vector< Meeting > & meetings, Vector< size_t > & allIds);
  int readMeetingsFromFile(const std::string & filename, Vector< Meeting > & meetings, Vector< size_t > & allIds);
  void parseCommandLine(const std::string & line, Vector< std::string > & tokens);

}

#endif
