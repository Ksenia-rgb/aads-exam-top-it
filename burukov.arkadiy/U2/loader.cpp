#include "loader.hpp"

#include <istream>
#include <string>

#include <parser.hpp>
#include <person.hpp>

namespace burukov
{

  void loadPersons(std::istream& in, Graph& graph)
  {
    std::string line;
    while (std::getline(in, line))
    {
      Person p{0, ""};
      if (parseLine(line, p) != PARSE_OK)
      {
        continue;
      }
      Vertex* existing = findVertex(graph, p.id);
      if (existing && existing->described)
      {
        continue;
      }
      Vertex& vertex = obtainVertex(graph, p.id);
      vertex.description = p.info;
      vertex.described = true;
    }
  }

  bool loadMeetings(std::istream& in, Graph& graph)
  {
    size_t first = 0;
    size_t second = 0;
    size_t duration = 0;
    while (in >> first >> second >> duration)
    {
      addMeeting(graph, first, second, duration);
    }
    return in.eof();
  }

}
