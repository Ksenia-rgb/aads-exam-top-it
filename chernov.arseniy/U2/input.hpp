#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <meeting.hpp>
#include <vector.hpp>

namespace chernov {

  bool parseArgs(int argc, char ** argv, std::string & inFile, std::string & dataFile);
  int readMeetings(const std::string & filename, Vector< Meeting > & meetings, Vector< size_t > & allIds);

}

#endif
