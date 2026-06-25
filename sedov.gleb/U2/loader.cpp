#include "loader.hpp"
#include <cstddef>
#include <istream>
#include <string>
#include "person.hpp"
#include "person_io.hpp"

void sedov::loadPersons(std::istream & in, Graph *& root)
{
  Person person{0, std::string()};
  bool valid = false;
  while (readPerson(in, person, valid))
  {
    if (!valid)
    {
      continue;
    }
    Graph * found = findBst(root, person.id);
    if (found != nullptr)
    {
      continue;
    }
    Vertex vertex{ person.info, true, nullptr };
    insertBst(root, person.id, vertex);
  }
}

bool sedov::loadMeetings(std::istream & in, Graph *& root)
{
  size_t first = 0;
  size_t second = 0;
  size_t duration = 0;
  while (in >> first >> second >> duration)
  {
    addMeeting(root, first, second, duration);
  }
  return in.eof();
}
